// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com

package ocsf.client;

import java.io.*;
import java.net.*;

/**
 * AbstractClient 是一個包含了在 client-server architecture 中客戶端的所有需要 method 的抽象 instance，
 * 當客戶端連線到伺服器端時，兩個程式可以交換 Object instances
 * handleMessageFromServer 方法必須由具體的 subclass 來實作
 * 必須由具體的 subclass 來定義 handleMessageFromServer method，
 * 並且其他的 hook method 也可以 override
 * 提供了幾個 public method，給使用這個 framework 的應用程式使用
 * <p>
 * Project Name: OCSF (Object Client-Server Framework)
 * <p>
 * 
 * @author Dr. Robert Lagani&egrave;re
 * @author Dr. Timothy C. Lethbridge
 * @author Fran&ccedil;ois B&eacutel;langer
 * @author Paul Holden
 * @version February 2001 (2.12)
 */
public abstract class AbstractClient implements Runnable {

	// INSTANCE VARIABLES ***********************************************

	/**
	 * Socket 在作業系統中被用作兩個 process 之間的溝通 channel
	 * 
	 * @see java.net.Socket
	 */
	private Socket				clientSocket;	// 用於連線伺服器的 Socket

	/**
	 * 用於處理發送給伺服器的資料的 stream
	 */
	private ObjectOutputStream	output;

	/**
	 * 用於處理從伺服器接收的資料的 stream
	 */
	private ObjectInputStream	input;

	/**
	 * 用於讀取伺服器傳來資料的 thread
	 */
	private Thread				clientReader;

	/**
	 * thread 是否準備停止，需要這個變數以便在 run method 的 loop 中知道何時停止等待訊息傳入
	 */
	private boolean				readyToStop	= false;

	/**
	 * 伺服器的 hostname
	 */
	private String				host;

	/**
	 * port 號碼
	 */
	private int					port;

	// CONSTRUCTORS *****************************************************

	/**
	 * client 的 constructor，需要指定伺服器的 hostname 和 port 號碼
	 * 
	 * @param host
	 *            server 的 hostname.
	 * @param port
	 *            port 號碼
	 */
	public AbstractClient(String host, int port) {
		// Initialize variables
		this.host = host;
		this.port = port;
	}

	// INSTANCE METHODS *************************************************

	/**
	 * 打開與伺服器的連線。如果連線已經打開，此呼叫不會產生任何效果。
	 * 
	 * @exception IOException
	 *                當打開連線時所發生的 I/O exception
	 */
	final public void openConnection() throws IOException {
		// 如果連線已經打開就不執行任何操作
		if (isConnected())
			return;

		// 建立 Socket 和資料 streams
		try {
			clientSocket = new Socket(host, port);
			output = new ObjectOutputStream(clientSocket.getOutputStream());
			input = new ObjectInputStream(clientSocket.getInputStream());
		} catch (IOException ex)
		// 當其中一個物件無法建立時，需要關閉前面建立的那三個物件
		{
			try {
				closeAll();
			} catch (Exception exc) {
			}

			throw ex; // 重新拋出 exception
		}

		clientReader = new Thread(this); // 建立接收資料的 thread
		readyToStop = false;
		clientReader.start(); // 啓動 thread
	}

	/**
	 * 向伺服器傳送 object (msg)，這是與伺服器進行通訊的唯一 method
	 * 
	 * @param msg
	 *            要傳送的訊息。
	 * @exception IOException
	 *                當傳送時所發生的 I/O exception
	 */
	final public void sendToServer(Object msg) throws IOException {
		if (clientSocket == null || output == null)
			throw new SocketException("socket does not exist");

		output.writeObject(msg);
	}

	/**
	 * 重置 object output stream，以便可以重複使用相同的 buffer
 	 * 通常不會使用此 method，只有在 Java 認為已經發送的資料需要重新傳送時會用到
	 */
	final public void forceResetAfterSend() throws IOException {
      output.reset();
	}

	/**
	 * 關閉與伺服器間的 connection
	 * 
	 * @exception IOException
	 *                當關閉時所發生的 I/O exception
	 */
	final public void closeConnection() throws IOException {
		// 防止執行緒卡在 loop 中
		readyToStop = true;

		try {
			closeAll();
		} finally {
			// 呼叫hook method
			connectionClosed();
		}
	}

	// ACCESSING METHODS ------------------------------------------------

	/**
	 * @return 如果 client 已經連線到伺服器，回傳 true，否則回傳 false。
	 */
	final public boolean isConnected() {
		return clientReader != null && clientReader.isAlive();
	}

	/**
	 * @return port 號碼
	 */
	final public int getPort() {
		return port;
	}

	/**
	 * 設置下一個連線的伺服器 port 號碼，
	 * 更改 port 只會在下一次呼叫 openConnection() 時生效
	 * 
	 * @param port
	 *            port 號碼
	 */
	final public void setPort(int port) {
		this.port = port;
	}

	/**
	 * @return hostname.
	 */
	final public String getHost() {
		return host;
	}

	/**
	 * 設置下一個連線的伺服器 host，
	 * 更改 host 只會在下一次呼叫 openConnection() 時生效
	 * 
	 * @param host
	 *            hostname
	 */
	final public void setHost(String host) {
		this.host = host;
	}

	/**
	 * 返回客戶端的 description，包含 hostname 和 port 號碼
	 * 
	 * @return 客戶端的 Inet address
	 */
	final public InetAddress getInetAddress() {
		return clientSocket.getInetAddress();
	}

	// RUN METHOD -------------------------------------------------------

	/**
	 * 等待從伺服器接收訊息。當每個訊息到達時，
	 * 會調用 handleMessageFromServer()，不應該直接呼叫此方法
	 */
	final public void run() {
		connectionEstablished();

		// 從伺服器來的訊息
		Object msg;

		// looping 等待資料

		try {
			while (!readyToStop) {
				// 從伺服器獲取資料並將其發送給 handler
				// thread 在以下 statement 持續等待，直到從伺服器接收到資料
				msg = input.readObject();

				// subclasses 需要根據處理訊息的方式不同來 implement 下列 method	
				handleMessageFromServer(msg);
			}
		} catch (Exception exception) {
			if (!readyToStop) {
				try {
					closeAll();
				} catch (Exception ex) {
				}

				connectionException(exception);
			}
		} finally {
			clientReader = null;
		}
	}

	// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

	/**
	 * 連線關閉後調用的 hook method，預設的 implementation 不執行任何操作
	 * 可以由 subclass override 以執行特殊處理，例如清理和終止，或嘗試重新連線
	 */
	protected void connectionClosed() {
	}

	/**
	 * 客戶端 thread 等待從伺服器接收訊息時，
	 * 如果引發了 exception，則調用此 hook method
	 * subclass 可以 override 此 method
	 * 
	 * @param exception
	 *            引發的 exception
	 */
	protected void connectionException(Exception exception) {
	}

	/**
	 * 在建立連線後調用的 hook method，預設的 implementation 不執行任何操作
	 * subclass 可以針對 override 此 method 來滿足特殊需求
	 */
	protected void connectionEstablished() {
	}

	/**
	 * 這是一個抽象方法，處理從伺服器收到的訊息
	 * 需要由具體的 subclass override
	 * 
	 * @param msg
	 *            從伺服器接收的訊息
	 */
	protected abstract void handleMessageFromServer(Object msg);

	// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

	/**
	 * 關閉所有連線資源
	 * 
	 * @exception IOException
	 *                在關閉時所發生的 I/O exception
	 */
	private void closeAll() throws IOException {
		try {
			// 關閉 socket
			if (clientSocket != null)
				clientSocket.close();

			// 關閉 output stream
			if (output != null)
				output.close();

			// 關閉 input stream
			if (input != null)
				input.close();
		} finally {
			// 設定 streams 和 sockets to NULL，
			// 以便 garbage collector 可以回收它們
			output = null;
			input = null;
			clientSocket = null;
		}
	}
}
// end of AbstractClient class
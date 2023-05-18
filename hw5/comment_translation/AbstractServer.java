// This file contains material supporting section 3.8 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package ocsf.server;

import java.net.*;
import java.util.*;
import java.io.*;


/**
* AbstractServer 類別維護一個thread，等待客戶端的連線嘗試
* 當連線嘗試發生時，它會以建立一個新的 ConnectionToClient instance，並且以一個 thread 來執行
* 當一個客戶端連線到伺服器端時，這兩個程式可以交換 Object instances
*
* handleMessageFromClient method 需要被具體的 subclass 來定義
* 其他的 hook method 也可以被 override
*
* 提供了一些對使用此 framework 的 app 有用的 public method，以及一些 hook method
*
* Project Name: OCSF (Object Client-Server Framework)<p>
*
* @author Dr Robert Lagani&egrave;re
* @author Dr Timothy C. Lethbridge
* @author Fran&ccedil;ois B&eacute;langer
* @author Paul Holden
* @version February 2001 (2.12)
* @see ocsf.server.ConnectionToClient
*/
public abstract class AbstractServer implements Runnable
{
  // INSTANCE VARIABLES *********************************************

  /**
   * 伺服器 socket：用於 listen 要連線的客戶端
   */
  private ServerSocket serverSocket = null;

  /**
   * 用來 listen 連線的 thread
   */
  private Thread connectionListener;

  /**
   * port 號碼
   */
  private int port;

  /**
   * 伺服器在接受連線時的 timeout
   * 超時後，伺服器將檢查是否發出有停止伺服器的 command
   * 如果沒有，它將繼續接受連線
   * 預設為 0.5 秒
   */
  private int timeout = 500;

  /**
   * 最大 queue 長度；即可以等待連線的最大客戶端數量
   * 預設為10個
   */
  private int backlog = 10;

  /**
   * 與客戶端 thread 相關聯的 thread 群組，
   * thread 群組的每個成員都是一個 ConnectionToClient
   */
  private ThreadGroup clientThreadGroup;

  /**
   * listening thread 是否準備停止。預設為 false
   */
  private boolean readyToStop = false;


// CONSTRUCTOR ******************************************************

  /**
   * 建立一個新的伺服器
   *
   * @param port 要 listen 的 port 號碼
   */
  public AbstractServer(int port)
  {
    this.port = port;

    this.clientThreadGroup =
      new ThreadGroup("ConnectionToClient threads")
      {
        // 所有在 connection thread 中未捕捉的 exception 都會被送到 clientException callback method
        public void uncaughtException(
          Thread thread, Throwable exception)
        {
          clientException((ConnectionToClient)thread, exception);
        }
      };
  }


// INSTANCE METHODS *************************************************

  /**
   * 開始等待新客戶端的thread
   * 如果伺服器已經在listening，此呼叫不會產生任何效果
   *
   * @exception IOException 建立伺服器 socket 時所發生的 I/O exception
   */
  final public void listen() throws IOException
  {
    if (!isListening())
    {
      if (serverSocket == null)
      {
        serverSocket = new ServerSocket(getPort(), backlog);
      }

      serverSocket.setSoTimeout(timeout);
      readyToStop = false;
      connectionListener = new Thread(this);
      connectionListener.start();
    }
  }

  /**
   * 使伺服器停止接受來自客戶端的新連線
   */
  final public void stopListening()
  {
    readyToStop = true;
  }

  /**
   * 關閉伺服器 socket，以及與所有客戶端的連線
   * 關閉客戶端時所發生的 exception 都會被忽略
   * 如果想要捕捉這些 exception，則必須在呼叫此 method 之前，先個別關閉客戶端
   * 如果此 thread 正在執行，此 method 也會停止 listening
   * 如果伺服器已經關閉，此呼叫不會產生任何效果
   *
   * @exception IOException 如果在關閉伺服器 socket 時所發生的 I/O exception
   */
  final synchronized public void close() throws IOException
  {
    if (serverSocket == null)
      return;
      stopListening();
    try
    {
      serverSocket.close();
    }
    finally
    {
      // 關閉已連線的客戶端 socket
      Thread[] clientThreadList = getClientConnections();
      for (int i=0; i<clientThreadList.length; i++)
      {
         try
         {
           ((ConnectionToClient)clientThreadList[i]).close();
         }
         // 忽略關閉客戶端時拋出的所有 exception
         catch(Exception ex) {}
      }
      serverSocket = null;
      serverClosed();
    }
  }

  /**
   * 將消息發送給連線到伺服器的每個客戶端 (broadcast)
   * 這只是一個 utility，subclass 可能想要在實際發送消息給所有客戶端之前做一些檢查
   * 此 method 可以被 override，但如果這樣做，
   * 它仍應執行發送給所有客戶端的一般功能，可能在做某種過濾之後再發送
   * 發送消息給特定客戶端時所拋出的任何 exception 都會被忽略
   *
   * @param msg   要發送的消息 (object)
   */
  public void sendToAllClients(Object msg)
  {
    Thread[] clientThreadList = getClientConnections();

    for (int i=0; i<clientThreadList.length; i++)
    {
      try
      {
        ((ConnectionToClient)clientThreadList[i]).sendToClient(msg);
      }
      catch (Exception ex) {}
    }
  }


// ACCESSING METHODS ------------------------------------------------

  /**
   * 如果伺服器準備號要接受新的客戶端，就 return true
   *
   * @return true 如果 server 正在 listening
   */
  final public boolean isListening()
  {
    return (connectionListener != null);
  }

  /**
   * return 一個包含現有客戶端連線的 array
   * 這可以被 concrete subclasses 使用，
   * 以實作對每個連線執行某些動作的訊息 (e.g. kill it, 傳送訊息等)
   * 記住，當此 array 被取得之後，某些客戶端可能會斷線
   * 新的客戶端也可以連線，這些後來的客戶端不會出現在此 array 中
   *
   * @return 包含 ConnectionToClient instance 的 Thread array
   */
  synchronized final public Thread[] getClientConnections()
  {
    Thread[] clientThreadList = new
      Thread[clientThreadGroup.activeCount()];

    clientThreadGroup.enumerate(clientThreadList);

    return clientThreadList;
  }

  /**
   * 計算當前已連線的客戶端數量
   *
   * @return 當前已連線的客戶端數量
   */
  final public int getNumberOfClients()
  {
    return clientThreadGroup.activeCount();
  }

  /**
   * Returns port 號碼
   *
   * @return port 號碼
   */
  final public int getPort()
  {
    return port;
  }

  /**
   * 設置下一個連線的 port 號碼
   * 伺服器必須關閉並重新啟動，才能讓 port 的改變生效
   *
   * @param port port 號碼
   */
  final public void setPort(int port)
  {
    this.port = port;
  }

  /**
   * 設置接受連線時的 timeout
   * 預設值是半秒
   * 這表示停止伺服器可能需要超過預設值才能真正停止
   * 伺服器必須停止並重新啟動，才能讓 timeout 的改變生效
   *
   * @param timeout timeout 毫秒數
   */
  final public void setTimeout(int timeout)
  {
    this.timeout = timeout;
  }

  /**
   * 設置 OS 接受的最大等待連線數，預設值為 20 個
   * 伺服器必須關閉並重新啟動，才能讓 backlog 的改變生效
   *
   * @param backlog 最大連線數
   */
  final public void setBacklog(int backlog)
  {
    this.backlog = backlog;
  }

// RUN METHOD -------------------------------------------------------

  /**
   * 執行監聽客戶端連線的 thread
   * 不可以被調用
   */
  final public void run()
  {
    // 呼叫 hook method，通知伺服器正在啟動
    serverStarted();

    try
    {
      // 重複等待新的客戶端連線，並接受它，然後啟動新的 thread 來處理數據交換
      while(!readyToStop)
      {
        try
        {
          // 在此等待新的連線嘗試或 timeout
          Socket clientSocket = serverSocket.accept();

          // 當接受到客戶端時，創建一個 thread 來處理數據交換，
          // 然後將其添加到 thread group

          synchronized(this)
          {
            ConnectionToClient c = new ConnectionToClient(
              this.clientThreadGroup, clientSocket, this);
          }
        }
        catch (InterruptedIOException exception)
        {
          // 當超時發生時，將拋出此 exception
          // 如果不準備停止，伺服器將繼續 listening
        }
      }

      // 呼叫 hook method 通知伺服器已停止監聽
      serverStopped();
    }
    catch (IOException exception)
    {
      if (!readyToStop)
      {
        // 關閉 socket 必須丟出 SocketException
        listeningException(exception);
      }
      else
      {
        serverStopped();
      }
    }
    finally
    {
      readyToStop = true;
      connectionListener = null;
    }
  }


// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

  /**
   * hook method，當接受到新的客戶端連線時被調用，預設不執行任何操作
   * @param client 與客戶端相連的連線

   */
  protected void clientConnected(ConnectionToClient client) {}

  /**
   * hook method，當客戶端斷線時被調用，預設不執行任何操作
   * 此方法可以被 subclass override，但是必須保持 synchronized
   *
   * @param client 與客戶端相連的連線
   */
  synchronized protected void clientDisconnected(
    ConnectionToClient client) {}

  /**
   * hook method，當 ConnectionToClient thread 拋出 exception 時被調用
   * 此方法可以被 subclass override，但是必須保持 synchronized
   *
   * @param client raise exception 的 客戶端
   * @param Throwable 丟出的 exception
   */
  synchronized protected void clientException(
    ConnectionToClient client, Throwable exception) {}

  /**
   * hook method，在 exception 發生時被調用，用來停止接受連線
   * 預設不執行任何操作
   * 此方法可以被 subclass override
   * 
   *
   * @param exception raise 的 exception
   */
  protected void listeningException(Throwable exception) {}

  /**
   * hook method，當伺服器開始 listen 連線時被調用，預設不執行任何操作
   * 此方法可以被 subclass override
   */
  protected void serverStarted() {}

  /**
   * hook method，當伺服器停止接受 client 連線時被調用，預設不執行任何操作
   * 此方法可以被 subclass override
   */
  protected void serverStopped() {}

  /**
   * hook method，當伺服器關閉時被調用，預設不執行任何操作
   * 此方法可以被 subclass override
   * 如果伺服器在監聽中時關閉，也會調用 serverStopped() method
   */
  protected void serverClosed() {}

  /**
   * 處理從客戶端發送到伺服器的 command
   * 這個 method 必須被 subclass 實現，subclass 應該對 message 做出回應
   * 此 method 由 synchronized method 呼叫，所以它也是 implcitly synchronized
   *
   * @param msg   發送的訊息
   * @param client 發送 message 的 client 的連線
   * 
   */
  protected abstract void handleMessageFromClient(
    Object msg, ConnectionToClient client);


// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

  /**
   * 接收從客戶端發送到伺服器的 command
   * 被 ConnectionToClient 的 run method 呼叫，
   * 此 method 會 listen 從伺服器發送的訊息
   * 此 method 是 synchronized 的，以確保它不會與其他 thread 衝突
   * 此 method 只是呼叫 handleMessageFromClient slot method
   *
   * @param msg   發送的訊息
   * @param client 發送 message 的 client 的連線
   */
  final synchronized void receiveMessageFromClient(
    Object msg, ConnectionToClient client)
  {
    this.handleMessageFromClient(msg, client);
  }
}
// End of AbstractServer Class

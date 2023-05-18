// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

import java.io.*;
import ocsf.server.*;

/**
 * 這個 class 繼承了 AbstractServer(abstract superclass)，並且 override 了一些 method 以便提供更多功能給伺服器端
 *
 * @author Dr Timothy C. Lethbridge
 * @author Dr Robert Lagani&egrave;re
 * @author Fran&ccedil;ois B&eacute;langer
 * @author Paul Holden
 * @version July 2000
 */
public class EchoServer extends AbstractServer 
{
  //Class variables *************************************************
  
  /**
   * 要使用的預設 port 號碼
   */
  final public static int DEFAULT_PORT = 5555;
  
  //Constructors ****************************************************
  
  /**
   * 建立一個 echo server 的 instance
   *
   * @param port 用來 listen 連線的 port 號碼
   */
  public EchoServer(int port) 
  {
    super(port);
  }

  
  //Instance methods ************************************************
  
  /**
   * 這個 method 處理從客戶端收到的任何訊息
   * 
   * @param msg 從客戶端收到的訊息
   * @param client 訊息來源的連線
   */
  public void handleMessageFromClient
    (Object msg, ConnectionToClient client)
  {
    System.out.println("Message received: " + msg + " from " + client);
    this.sendToAllClients(msg);
  }
    
  /**
   * 這個 method override 了 superclass 的 method
   * 當伺服器開始 listen 連線時，這個 method 會被呼叫
   */
  protected void serverStarted()
  {
    System.out.println
      ("Server listening for connections on port " + getPort());
  }
  
  /**
   * 這個 method override 了 superclass 的 method
   * 當伺服器停止 listen 連線時，這個 method 會被呼叫
   * 
   */
  protected void serverStopped()
  {
    System.out.println
      ("Server has stopped listening for connections.");
  }
  
  //Class methods ***************************************************
  
  /**
   * 這個 method 負責建立伺服器的 instance (在這個階段沒有 UI)
   *
   * @param args[0] 要 listen 的 port number，如果沒有輸入參數的話預設是 5555 
   */

  public static void main(String[] args) 
  {
    int port = 0; // 要 listen 的 port number

    try
    {
      port = Integer.parseInt(args[0]); // 從 command line 讀取 port number (args[0])
    }
    catch(Throwable t)
    {
      port = DEFAULT_PORT; // 將 port 設成 5555
    }
	
    EchoServer sv = new EchoServer(port);
    
    try 
    {
      sv.listen(); // 開始 listen 連線
    } 
    catch (Exception ex) 
    {
      System.out.println("ERROR - Could not listen for clients!");
    }
  }
}
//End of EchoServer class

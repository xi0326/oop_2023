package ocsf.server;

import java.io.*;
import java.util.ArrayList;

/**
 * This class overrides some of the methods in the abstract 
 * superclass in order to give more functionality to the server.
 */
public class CalculateServer extends AbstractServer 
{
  //Class variables *************************************************
  
  /**
   * The default port to listen on.
   */
  final public static int DEFAULT_PORT = 5555;
  
  //Constructors ****************************************************
  
  /**
   * Constructs an instance of the echo server.
   *
   * @param port The port number to connect on.
   */
  public CalculateServer(int port) 
  {
    super(port);
  }

  
  //Instance methods ************************************************
  
  /**
   * This method handles any messages received from the client.
   *
   * @param msg The message received from the client.
   * @param client The connection from which the message originated.
   * 
   * the server will get the input from the client
   * input should be an ArrayList of Integers
   * input: first number (integer), the operator (1234 -> +-*÷), and the second number (integer)
   * the server will calculate the result and send it back to the client
   * 
   */
  public void handleMessageFromClient
    (Object msg, ConnectionToClient client)
  {
    // cast the message to an ArrayList of Integers (downcast from Object)
    ArrayList<Integer> msg_ArrayList = (ArrayList<Integer>) msg;

    // parse the integers from the arraylist
    int firstNum = msg_ArrayList.get(0);
    int operator = msg_ArrayList.get(1);
    int secondNum = msg_ArrayList.get(2);

    System.out.println("Message received: " + msg + " from " + client);

    // do the calculation, and send the result back to the client
    if (operator == 1)  // addition
    {
      System.out.println("result: " + (firstNum + secondNum));
      this.sendToAllClients(firstNum + secondNum);
    }
    else if (operator == 2) // subtraction
    {
      System.out.println("result: " + (firstNum - secondNum));
      this.sendToAllClients(firstNum - secondNum);
    }
    else if (operator == 3) // multiplication
    {
      System.out.println("result: " + (firstNum * secondNum));
      this.sendToAllClients(firstNum * secondNum);
    }
    else if (operator == 4) // division
    {
      // if secondNum is 0, cannot divide by zero
      if (secondNum == 0)
      {
        System.out.println("Cannot divide by zero");
        this.sendToAllClients("Cannot divide by zero");
      }
      else
      {
        System.out.println("result: " + ((double) firstNum / secondNum));
        this.sendToAllClients((double) firstNum / secondNum);
      }
    }
    else
    {
      System.out.println("Invalid operator");
      this.sendToAllClients("Invalid operator");
    }
  }
    
  /**
   * This method overrides the one in the superclass.  Called
   * when the server starts listening for connections.
   */
  protected void serverStarted()
  {
    System.out.println
      ("Server listening for connections on port " + getPort());
  }
  
  /**
   * This method overrides the one in the superclass.  Called
   * when the server stops listening for connections.
   */
  protected void serverStopped()
  {
    System.out.println
      ("Server has stopped listening for connections.");
  }
  
  //Class methods ***************************************************
  
  /**
   * This method is responsible for the creation of 
   * the server instance (there is no UI in this phase).
   *
   * @param args[0] The port number to listen on.  Defaults to 5555 
   *          if no argument is entered.
   */
  public static void main(String[] args) 
  {
    int port; // Port to listen on

    try
    {
      port = Integer.parseInt(args[0]); // Get port from command line
    }
    catch(Throwable t)
    {
      port = DEFAULT_PORT; // Set port to 5555
    }
	
    CalculateServer server = new CalculateServer(port);
    
    try 
    {
      server.listen(); // Start listening for connections
    } 
    catch (Exception ex) 
    {
      System.out.println("ERROR - Could not listen for clients!");
    }
  }
}
//End of CalculateServer class

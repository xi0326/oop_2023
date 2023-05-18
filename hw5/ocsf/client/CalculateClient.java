package ocsf.client;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class CalculateClient extends AbstractClient
{
    // constructor
    public CalculateClient(final String HOST, final int PORT)
    {
        super(HOST, PORT);
    }

    // instance methods
    protected synchronized void handleMessageFromServer(Object msg)
    {
        System.out.println("Message received: " + msg);
        notify();
    }

    /* the method for the user interface
     * the user can enter the first number (integer), the operator (1234 -> +-*÷), and the second number (integer)
     * the client will send the message to the server
     * finally the client will print the result
     */
    protected synchronized void calculationInterface()
    {
        // initialise scanner
        Scanner scanner = new Scanner(System.in);
        
        // open connection
        try
        {
            this.openConnection();
        }
        catch(IOException e)
        {
            System.out.println("Cannot open connection. Terminating client...");
            System.exit(1);
        }

        // get input from user
        try
        {
            while (true)
            {
                ArrayList<Integer> msg = new ArrayList<Integer>(3);
                    
                System.out.println("Enter first number: ");
                msg.add(scanner.nextInt());
                System.out.println("Enter operator: (1234 => +-*/)");
                msg.add(scanner.nextInt());
                System.out.println("Enter second number: ");
                msg.add(scanner.nextInt());

                // send message to server
                this.sendToServer(msg);
                
                // wait for server to respond
                try
                {
                    wait();
                }
                catch(InterruptedException ex)
                {
                    ex.printStackTrace();
                    System.out.println("Thread interrupted");
                }
                
            }
            
        }
        catch(IOException exc)
        {
            System.out.println("Cannot send message to server. Terminating client.");
            System.exit(1);
        }

        scanner.close();
    }

    public static void main(String[] args)
    {
        // iniitialise client
        final String HOST = "127.0.0.1"; // Host to connect to localhost
        final int PORT = 5555; // Port to connect on

        CalculateClient client = new CalculateClient(HOST, PORT);

        // test client, ctrl-c to exit
        client.calculationInterface();


    }
}
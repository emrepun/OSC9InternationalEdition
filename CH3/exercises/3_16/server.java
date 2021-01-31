import java.net.*;
import java.io.*;

class Server {
  public static void main(String[] args) {
    try {
      ServerSocket sock = new ServerSocket(6017);

      while(true) {
        Socket client = sock.accept();

        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

        pout.println("Today's quote: The only thing that is constant is change.");

        client.close();
      }
    }
    catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}

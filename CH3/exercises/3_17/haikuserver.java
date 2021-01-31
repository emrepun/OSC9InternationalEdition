import java.net.*;
import java.io.*;

class HaikuServer {
  public static void main(String[] args) {
    try {
      ServerSocket sock = new ServerSocket(5575);

      while(true) {
        Socket client = sock.accept();

        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

        pout.println("An ocean voyage.");
        pout.println("As waves break over the bow,");
        pout.println("the sea welcomes me.");

        client.close();
      }
    }
    catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}

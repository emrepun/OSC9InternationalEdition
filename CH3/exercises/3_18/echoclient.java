import java.net.*;
import java.io.*;

class EchoClient {
  public static void main(String[] args) {
    try {
      Socket sock = new Socket("127.0.0.1", 5575);

      // create a writer to write to output stream of the server
      PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);

      for (int i = 0; i < args.length; i++) {
        pout.println(args[i]);
      }

      // create a reader from server's input stream to read.
      InputStream in = sock.getInputStream();
      BufferedReader bin = new BufferedReader(new InputStreamReader(in));

      String line;
      while ( (line = bin.readLine()) != null) {
        System.out.println(line);
      }

      sock.close();
    }
    catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}

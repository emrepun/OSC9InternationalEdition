import java.net.*;
import java.io.*;

class EchoServer {
  public static void main(String[] args) {
    try {
      ServerSocket sock = new ServerSocket(5575);

      while(true) {
        Socket client = sock.accept();

        // create a writer to write to client's output stream.
        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

        // create a reader to read from client's intput stream.
        InputStream in = client.getInputStream();
        BufferedReader bin = new BufferedReader(new InputStreamReader(in));

        String line;

        while ( (line = bin.readLine()) != null) {
          pout.println(line);
        }

        client.close();
      }
    }
    catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}

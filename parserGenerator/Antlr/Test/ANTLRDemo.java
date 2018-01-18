import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ANTLRDemo {
    public static void main(String[] args) throws Exception {
        //String query = "<!doctype html>";
        String query = readFile("abc.com.html");
        ANTLRInputStream input = new ANTLRInputStream(query);
        HTMLLexer lexer = new HTMLLexer(input);
        // CommonTokenStream tokens = new CommonTokenStream(lexer);
        // HTMLParser parser = new HTMLParser(tokens);
        // ParseTree tree = parser.htmlDocument(); // begin parsing at query rule
        // //System.out.println(tree.toStringTree(parser)); // print LISP-style tree
    }

    static String readFile(String path) 
	  throws IOException 
	{
	  byte[] encoded = Files.readAllBytes(Paths.get(path));
	  return new String(encoded, "UTF-8");
	}
}
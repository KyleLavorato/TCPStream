import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ANTLRDemo {
    public static void main(String[] args) throws Exception {
        
        try {
            String query = readFile("TestFiles/class.cpp");
            
            ANTLRInputStream input = new ANTLRInputStream(query);
            CPP14Lexer lexer = new CPP14Lexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            CPP14Parser parser = new CPP14Parser(tokens);
            
            parser.setErrorHandler(new BailErrorStrategy());
            ParseTree tree = parser.translationunit(); // begin parsing at query rule

            ParseTreeWalker walker = new ParseTreeWalker();
            AntlrCPP14Listener listener = new AntlrCPP14Listener();
            walker.walk(listener, tree);

            //System.out.println(tree.toStringTree(parser)); // print LISP-style tree
            System.out.println("SUCCESS");
        } catch(Exception e) {
            System.out.println("FAILURE");
            System.out.println(e);
        }
    }

    static String readFile(String path) 
	  throws IOException 
	{
	  byte[] encoded = Files.readAllBytes(Paths.get(path));
	  return new String(encoded, "UTF-8");
	}
}
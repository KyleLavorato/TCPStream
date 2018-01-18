import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class AntlrCPP14Listener extends CPP14BaseListener {
    
    @Override
    public void enterClasshead(CPP14Parser.ClassheadContext ctx) {
        System.out.println(ctx.getText());
    }
}

// Generated from HTMLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HTMLParserListener.h"


/**
 * This class provides an empty implementation of HTMLParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  HTMLParserBaseListener : public HTMLParserListener {
public:

  virtual void enterHtmlDocument(HTMLParser::HtmlDocumentContext * /*ctx*/) override { }
  virtual void exitHtmlDocument(HTMLParser::HtmlDocumentContext * /*ctx*/) override { }

  virtual void enterHtmlElements(HTMLParser::HtmlElementsContext * /*ctx*/) override { }
  virtual void exitHtmlElements(HTMLParser::HtmlElementsContext * /*ctx*/) override { }

  virtual void enterHtmlElement(HTMLParser::HtmlElementContext * /*ctx*/) override { }
  virtual void exitHtmlElement(HTMLParser::HtmlElementContext * /*ctx*/) override { }

  virtual void enterHtmlContent(HTMLParser::HtmlContentContext * /*ctx*/) override { }
  virtual void exitHtmlContent(HTMLParser::HtmlContentContext * /*ctx*/) override { }

  virtual void enterHtmlAttribute(HTMLParser::HtmlAttributeContext * /*ctx*/) override { }
  virtual void exitHtmlAttribute(HTMLParser::HtmlAttributeContext * /*ctx*/) override { }

  virtual void enterHtmlAttributeName(HTMLParser::HtmlAttributeNameContext * /*ctx*/) override { }
  virtual void exitHtmlAttributeName(HTMLParser::HtmlAttributeNameContext * /*ctx*/) override { }

  virtual void enterHtmlAttributeValue(HTMLParser::HtmlAttributeValueContext * /*ctx*/) override { }
  virtual void exitHtmlAttributeValue(HTMLParser::HtmlAttributeValueContext * /*ctx*/) override { }

  virtual void enterHtmlTagName(HTMLParser::HtmlTagNameContext * /*ctx*/) override { }
  virtual void exitHtmlTagName(HTMLParser::HtmlTagNameContext * /*ctx*/) override { }

  virtual void enterHtmlChardata(HTMLParser::HtmlChardataContext * /*ctx*/) override { }
  virtual void exitHtmlChardata(HTMLParser::HtmlChardataContext * /*ctx*/) override { }

  virtual void enterHtmlMisc(HTMLParser::HtmlMiscContext * /*ctx*/) override { }
  virtual void exitHtmlMisc(HTMLParser::HtmlMiscContext * /*ctx*/) override { }

  virtual void enterHtmlComment(HTMLParser::HtmlCommentContext * /*ctx*/) override { }
  virtual void exitHtmlComment(HTMLParser::HtmlCommentContext * /*ctx*/) override { }

  virtual void enterXhtmlCDATA(HTMLParser::XhtmlCDATAContext * /*ctx*/) override { }
  virtual void exitXhtmlCDATA(HTMLParser::XhtmlCDATAContext * /*ctx*/) override { }

  virtual void enterDtd(HTMLParser::DtdContext * /*ctx*/) override { }
  virtual void exitDtd(HTMLParser::DtdContext * /*ctx*/) override { }

  virtual void enterXml(HTMLParser::XmlContext * /*ctx*/) override { }
  virtual void exitXml(HTMLParser::XmlContext * /*ctx*/) override { }

  virtual void enterScriptlet(HTMLParser::ScriptletContext * /*ctx*/) override { }
  virtual void exitScriptlet(HTMLParser::ScriptletContext * /*ctx*/) override { }

  virtual void enterScript(HTMLParser::ScriptContext * /*ctx*/) override { }
  virtual void exitScript(HTMLParser::ScriptContext * /*ctx*/) override { }

  virtual void enterStyle(HTMLParser::StyleContext * /*ctx*/) override { }
  virtual void exitStyle(HTMLParser::StyleContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


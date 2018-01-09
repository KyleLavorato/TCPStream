
// Generated from HTMLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HTMLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by HTMLParser.
 */
class  HTMLParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterHtmlDocument(HTMLParser::HtmlDocumentContext *ctx) = 0;
  virtual void exitHtmlDocument(HTMLParser::HtmlDocumentContext *ctx) = 0;

  virtual void enterHtmlElements(HTMLParser::HtmlElementsContext *ctx) = 0;
  virtual void exitHtmlElements(HTMLParser::HtmlElementsContext *ctx) = 0;

  virtual void enterHtmlElement(HTMLParser::HtmlElementContext *ctx) = 0;
  virtual void exitHtmlElement(HTMLParser::HtmlElementContext *ctx) = 0;

  virtual void enterHtmlContent(HTMLParser::HtmlContentContext *ctx) = 0;
  virtual void exitHtmlContent(HTMLParser::HtmlContentContext *ctx) = 0;

  virtual void enterHtmlAttribute(HTMLParser::HtmlAttributeContext *ctx) = 0;
  virtual void exitHtmlAttribute(HTMLParser::HtmlAttributeContext *ctx) = 0;

  virtual void enterHtmlAttributeName(HTMLParser::HtmlAttributeNameContext *ctx) = 0;
  virtual void exitHtmlAttributeName(HTMLParser::HtmlAttributeNameContext *ctx) = 0;

  virtual void enterHtmlAttributeValue(HTMLParser::HtmlAttributeValueContext *ctx) = 0;
  virtual void exitHtmlAttributeValue(HTMLParser::HtmlAttributeValueContext *ctx) = 0;

  virtual void enterHtmlTagName(HTMLParser::HtmlTagNameContext *ctx) = 0;
  virtual void exitHtmlTagName(HTMLParser::HtmlTagNameContext *ctx) = 0;

  virtual void enterHtmlChardata(HTMLParser::HtmlChardataContext *ctx) = 0;
  virtual void exitHtmlChardata(HTMLParser::HtmlChardataContext *ctx) = 0;

  virtual void enterHtmlMisc(HTMLParser::HtmlMiscContext *ctx) = 0;
  virtual void exitHtmlMisc(HTMLParser::HtmlMiscContext *ctx) = 0;

  virtual void enterHtmlComment(HTMLParser::HtmlCommentContext *ctx) = 0;
  virtual void exitHtmlComment(HTMLParser::HtmlCommentContext *ctx) = 0;

  virtual void enterXhtmlCDATA(HTMLParser::XhtmlCDATAContext *ctx) = 0;
  virtual void exitXhtmlCDATA(HTMLParser::XhtmlCDATAContext *ctx) = 0;

  virtual void enterDtd(HTMLParser::DtdContext *ctx) = 0;
  virtual void exitDtd(HTMLParser::DtdContext *ctx) = 0;

  virtual void enterXml(HTMLParser::XmlContext *ctx) = 0;
  virtual void exitXml(HTMLParser::XmlContext *ctx) = 0;

  virtual void enterScriptlet(HTMLParser::ScriptletContext *ctx) = 0;
  virtual void exitScriptlet(HTMLParser::ScriptletContext *ctx) = 0;

  virtual void enterScript(HTMLParser::ScriptContext *ctx) = 0;
  virtual void exitScript(HTMLParser::ScriptContext *ctx) = 0;

  virtual void enterStyle(HTMLParser::StyleContext *ctx) = 0;
  virtual void exitStyle(HTMLParser::StyleContext *ctx) = 0;


};


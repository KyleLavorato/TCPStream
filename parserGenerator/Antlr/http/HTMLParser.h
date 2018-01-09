
// Generated from HTMLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  HTMLParser : public antlr4::Parser {
public:
  enum {
    HTML_COMMENT = 1, HTML_CONDITIONAL_COMMENT = 2, XML_DECLARATION = 3, 
    CDATA = 4, DTD = 5, SCRIPTLET = 6, SEA_WS = 7, SCRIPT_OPEN = 8, STYLE_OPEN = 9, 
    TAG_OPEN = 10, HTML_TEXT = 11, TAG_CLOSE = 12, TAG_SLASH_CLOSE = 13, 
    TAG_SLASH = 14, TAG_EQUALS = 15, TAG_NAME = 16, TAG_WHITESPACE = 17, 
    SCRIPT_BODY = 18, SCRIPT_SHORT_BODY = 19, STYLE_BODY = 20, STYLE_SHORT_BODY = 21, 
    ATTVALUE_VALUE = 22, ATTRIBUTE = 23
  };

  enum {
    RuleHtmlDocument = 0, RuleHtmlElements = 1, RuleHtmlElement = 2, RuleHtmlContent = 3, 
    RuleHtmlAttribute = 4, RuleHtmlAttributeName = 5, RuleHtmlAttributeValue = 6, 
    RuleHtmlTagName = 7, RuleHtmlChardata = 8, RuleHtmlMisc = 9, RuleHtmlComment = 10, 
    RuleXhtmlCDATA = 11, RuleDtd = 12, RuleXml = 13, RuleScriptlet = 14, 
    RuleScript = 15, RuleStyle = 16
  };

  HTMLParser(antlr4::TokenStream *input);
  ~HTMLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class HtmlDocumentContext;
  class HtmlElementsContext;
  class HtmlElementContext;
  class HtmlContentContext;
  class HtmlAttributeContext;
  class HtmlAttributeNameContext;
  class HtmlAttributeValueContext;
  class HtmlTagNameContext;
  class HtmlChardataContext;
  class HtmlMiscContext;
  class HtmlCommentContext;
  class XhtmlCDATAContext;
  class DtdContext;
  class XmlContext;
  class ScriptletContext;
  class ScriptContext;
  class StyleContext; 

  class  HtmlDocumentContext : public antlr4::ParserRuleContext {
  public:
    HtmlDocumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ScriptletContext *> scriptlet();
    ScriptletContext* scriptlet(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEA_WS();
    antlr4::tree::TerminalNode* SEA_WS(size_t i);
    XmlContext *xml();
    DtdContext *dtd();
    std::vector<HtmlElementsContext *> htmlElements();
    HtmlElementsContext* htmlElements(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlDocumentContext* htmlDocument();

  class  HtmlElementsContext : public antlr4::ParserRuleContext {
  public:
    HtmlElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HtmlElementContext *htmlElement();
    std::vector<HtmlMiscContext *> htmlMisc();
    HtmlMiscContext* htmlMisc(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlElementsContext* htmlElements();

  class  HtmlElementContext : public antlr4::ParserRuleContext {
  public:
    HtmlElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TAG_OPEN();
    antlr4::tree::TerminalNode* TAG_OPEN(size_t i);
    std::vector<HtmlTagNameContext *> htmlTagName();
    HtmlTagNameContext* htmlTagName(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TAG_CLOSE();
    antlr4::tree::TerminalNode* TAG_CLOSE(size_t i);
    HtmlContentContext *htmlContent();
    antlr4::tree::TerminalNode *TAG_SLASH();
    std::vector<HtmlAttributeContext *> htmlAttribute();
    HtmlAttributeContext* htmlAttribute(size_t i);
    antlr4::tree::TerminalNode *TAG_SLASH_CLOSE();
    ScriptletContext *scriptlet();
    ScriptContext *script();
    StyleContext *style();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlElementContext* htmlElement();

  class  HtmlContentContext : public antlr4::ParserRuleContext {
  public:
    HtmlContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<HtmlChardataContext *> htmlChardata();
    HtmlChardataContext* htmlChardata(size_t i);
    std::vector<HtmlElementContext *> htmlElement();
    HtmlElementContext* htmlElement(size_t i);
    std::vector<XhtmlCDATAContext *> xhtmlCDATA();
    XhtmlCDATAContext* xhtmlCDATA(size_t i);
    std::vector<HtmlCommentContext *> htmlComment();
    HtmlCommentContext* htmlComment(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlContentContext* htmlContent();

  class  HtmlAttributeContext : public antlr4::ParserRuleContext {
  public:
    HtmlAttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HtmlAttributeNameContext *htmlAttributeName();
    antlr4::tree::TerminalNode *TAG_EQUALS();
    HtmlAttributeValueContext *htmlAttributeValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlAttributeContext* htmlAttribute();

  class  HtmlAttributeNameContext : public antlr4::ParserRuleContext {
  public:
    HtmlAttributeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TAG_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlAttributeNameContext* htmlAttributeName();

  class  HtmlAttributeValueContext : public antlr4::ParserRuleContext {
  public:
    HtmlAttributeValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ATTVALUE_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlAttributeValueContext* htmlAttributeValue();

  class  HtmlTagNameContext : public antlr4::ParserRuleContext {
  public:
    HtmlTagNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TAG_NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlTagNameContext* htmlTagName();

  class  HtmlChardataContext : public antlr4::ParserRuleContext {
  public:
    HtmlChardataContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HTML_TEXT();
    antlr4::tree::TerminalNode *SEA_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlChardataContext* htmlChardata();

  class  HtmlMiscContext : public antlr4::ParserRuleContext {
  public:
    HtmlMiscContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HtmlCommentContext *htmlComment();
    antlr4::tree::TerminalNode *SEA_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlMiscContext* htmlMisc();

  class  HtmlCommentContext : public antlr4::ParserRuleContext {
  public:
    HtmlCommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HTML_COMMENT();
    antlr4::tree::TerminalNode *HTML_CONDITIONAL_COMMENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HtmlCommentContext* htmlComment();

  class  XhtmlCDATAContext : public antlr4::ParserRuleContext {
  public:
    XhtmlCDATAContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CDATA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  XhtmlCDATAContext* xhtmlCDATA();

  class  DtdContext : public antlr4::ParserRuleContext {
  public:
    DtdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DTD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DtdContext* dtd();

  class  XmlContext : public antlr4::ParserRuleContext {
  public:
    XmlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *XML_DECLARATION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  XmlContext* xml();

  class  ScriptletContext : public antlr4::ParserRuleContext {
  public:
    ScriptletContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCRIPTLET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptletContext* scriptlet();

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCRIPT_OPEN();
    antlr4::tree::TerminalNode *SCRIPT_BODY();
    antlr4::tree::TerminalNode *SCRIPT_SHORT_BODY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptContext* script();

  class  StyleContext : public antlr4::ParserRuleContext {
  public:
    StyleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STYLE_OPEN();
    antlr4::tree::TerminalNode *STYLE_BODY();
    antlr4::tree::TerminalNode *STYLE_SHORT_BODY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleContext* style();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};


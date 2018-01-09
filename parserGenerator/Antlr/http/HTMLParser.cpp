
// Generated from HTMLParser.g4 by ANTLR 4.7


#include "HTMLParserListener.h"

#include "HTMLParser.h"


using namespace antlrcpp;
using namespace antlr4;

HTMLParser::HTMLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

HTMLParser::~HTMLParser() {
  delete _interpreter;
}

std::string HTMLParser::getGrammarFileName() const {
  return "HTMLParser.g4";
}

const std::vector<std::string>& HTMLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& HTMLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- HtmlDocumentContext ------------------------------------------------------------------

HTMLParser::HtmlDocumentContext::HtmlDocumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HTMLParser::ScriptletContext *> HTMLParser::HtmlDocumentContext::scriptlet() {
  return getRuleContexts<HTMLParser::ScriptletContext>();
}

HTMLParser::ScriptletContext* HTMLParser::HtmlDocumentContext::scriptlet(size_t i) {
  return getRuleContext<HTMLParser::ScriptletContext>(i);
}

std::vector<tree::TerminalNode *> HTMLParser::HtmlDocumentContext::SEA_WS() {
  return getTokens(HTMLParser::SEA_WS);
}

tree::TerminalNode* HTMLParser::HtmlDocumentContext::SEA_WS(size_t i) {
  return getToken(HTMLParser::SEA_WS, i);
}

HTMLParser::XmlContext* HTMLParser::HtmlDocumentContext::xml() {
  return getRuleContext<HTMLParser::XmlContext>(0);
}

HTMLParser::DtdContext* HTMLParser::HtmlDocumentContext::dtd() {
  return getRuleContext<HTMLParser::DtdContext>(0);
}

std::vector<HTMLParser::HtmlElementsContext *> HTMLParser::HtmlDocumentContext::htmlElements() {
  return getRuleContexts<HTMLParser::HtmlElementsContext>();
}

HTMLParser::HtmlElementsContext* HTMLParser::HtmlDocumentContext::htmlElements(size_t i) {
  return getRuleContext<HTMLParser::HtmlElementsContext>(i);
}


size_t HTMLParser::HtmlDocumentContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlDocument;
}

void HTMLParser::HtmlDocumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlDocument(this);
}

void HTMLParser::HtmlDocumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlDocument(this);
}

HTMLParser::HtmlDocumentContext* HTMLParser::htmlDocument() {
  HtmlDocumentContext *_localctx = _tracker.createInstance<HtmlDocumentContext>(_ctx, getState());
  enterRule(_localctx, 0, HTMLParser::RuleHtmlDocument);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(38);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(36);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case HTMLParser::SCRIPTLET: {
            setState(34);
            scriptlet();
            break;
          }

          case HTMLParser::SEA_WS: {
            setState(35);
            match(HTMLParser::SEA_WS);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(40);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(42);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HTMLParser::XML_DECLARATION) {
      setState(41);
      xml();
    }
    setState(48);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(46);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case HTMLParser::SCRIPTLET: {
            setState(44);
            scriptlet();
            break;
          }

          case HTMLParser::SEA_WS: {
            setState(45);
            match(HTMLParser::SEA_WS);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(50);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(52);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HTMLParser::DTD) {
      setState(51);
      dtd();
    }
    setState(58);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(56);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case HTMLParser::SCRIPTLET: {
            setState(54);
            scriptlet();
            break;
          }

          case HTMLParser::SEA_WS: {
            setState(55);
            match(HTMLParser::SEA_WS);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(60);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
    setState(64);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HTMLParser::HTML_COMMENT)
      | (1ULL << HTMLParser::HTML_CONDITIONAL_COMMENT)
      | (1ULL << HTMLParser::SCRIPTLET)
      | (1ULL << HTMLParser::SEA_WS)
      | (1ULL << HTMLParser::SCRIPT_OPEN)
      | (1ULL << HTMLParser::STYLE_OPEN)
      | (1ULL << HTMLParser::TAG_OPEN))) != 0)) {
      setState(61);
      htmlElements();
      setState(66);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlElementsContext ------------------------------------------------------------------

HTMLParser::HtmlElementsContext::HtmlElementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HTMLParser::HtmlElementContext* HTMLParser::HtmlElementsContext::htmlElement() {
  return getRuleContext<HTMLParser::HtmlElementContext>(0);
}

std::vector<HTMLParser::HtmlMiscContext *> HTMLParser::HtmlElementsContext::htmlMisc() {
  return getRuleContexts<HTMLParser::HtmlMiscContext>();
}

HTMLParser::HtmlMiscContext* HTMLParser::HtmlElementsContext::htmlMisc(size_t i) {
  return getRuleContext<HTMLParser::HtmlMiscContext>(i);
}


size_t HTMLParser::HtmlElementsContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlElements;
}

void HTMLParser::HtmlElementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlElements(this);
}

void HTMLParser::HtmlElementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlElements(this);
}

HTMLParser::HtmlElementsContext* HTMLParser::htmlElements() {
  HtmlElementsContext *_localctx = _tracker.createInstance<HtmlElementsContext>(_ctx, getState());
  enterRule(_localctx, 2, HTMLParser::RuleHtmlElements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(70);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HTMLParser::HTML_COMMENT)
      | (1ULL << HTMLParser::HTML_CONDITIONAL_COMMENT)
      | (1ULL << HTMLParser::SEA_WS))) != 0)) {
      setState(67);
      htmlMisc();
      setState(72);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(73);
    htmlElement();
    setState(77);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(74);
        htmlMisc(); 
      }
      setState(79);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlElementContext ------------------------------------------------------------------

HTMLParser::HtmlElementContext::HtmlElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HTMLParser::HtmlElementContext::TAG_OPEN() {
  return getTokens(HTMLParser::TAG_OPEN);
}

tree::TerminalNode* HTMLParser::HtmlElementContext::TAG_OPEN(size_t i) {
  return getToken(HTMLParser::TAG_OPEN, i);
}

std::vector<HTMLParser::HtmlTagNameContext *> HTMLParser::HtmlElementContext::htmlTagName() {
  return getRuleContexts<HTMLParser::HtmlTagNameContext>();
}

HTMLParser::HtmlTagNameContext* HTMLParser::HtmlElementContext::htmlTagName(size_t i) {
  return getRuleContext<HTMLParser::HtmlTagNameContext>(i);
}

std::vector<tree::TerminalNode *> HTMLParser::HtmlElementContext::TAG_CLOSE() {
  return getTokens(HTMLParser::TAG_CLOSE);
}

tree::TerminalNode* HTMLParser::HtmlElementContext::TAG_CLOSE(size_t i) {
  return getToken(HTMLParser::TAG_CLOSE, i);
}

HTMLParser::HtmlContentContext* HTMLParser::HtmlElementContext::htmlContent() {
  return getRuleContext<HTMLParser::HtmlContentContext>(0);
}

tree::TerminalNode* HTMLParser::HtmlElementContext::TAG_SLASH() {
  return getToken(HTMLParser::TAG_SLASH, 0);
}

std::vector<HTMLParser::HtmlAttributeContext *> HTMLParser::HtmlElementContext::htmlAttribute() {
  return getRuleContexts<HTMLParser::HtmlAttributeContext>();
}

HTMLParser::HtmlAttributeContext* HTMLParser::HtmlElementContext::htmlAttribute(size_t i) {
  return getRuleContext<HTMLParser::HtmlAttributeContext>(i);
}

tree::TerminalNode* HTMLParser::HtmlElementContext::TAG_SLASH_CLOSE() {
  return getToken(HTMLParser::TAG_SLASH_CLOSE, 0);
}

HTMLParser::ScriptletContext* HTMLParser::HtmlElementContext::scriptlet() {
  return getRuleContext<HTMLParser::ScriptletContext>(0);
}

HTMLParser::ScriptContext* HTMLParser::HtmlElementContext::script() {
  return getRuleContext<HTMLParser::ScriptContext>(0);
}

HTMLParser::StyleContext* HTMLParser::HtmlElementContext::style() {
  return getRuleContext<HTMLParser::StyleContext>(0);
}


size_t HTMLParser::HtmlElementContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlElement;
}

void HTMLParser::HtmlElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlElement(this);
}

void HTMLParser::HtmlElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlElement(this);
}

HTMLParser::HtmlElementContext* HTMLParser::htmlElement() {
  HtmlElementContext *_localctx = _tracker.createInstance<HtmlElementContext>(_ctx, getState());
  enterRule(_localctx, 4, HTMLParser::RuleHtmlElement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      match(HTMLParser::TAG_OPEN);
      setState(81);
      htmlTagName();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HTMLParser::TAG_NAME) {
        setState(82);
        htmlAttribute();
        setState(87);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(88);
      match(HTMLParser::TAG_CLOSE);
      setState(89);
      htmlContent();
      setState(90);
      match(HTMLParser::TAG_OPEN);
      setState(91);
      match(HTMLParser::TAG_SLASH);
      setState(92);
      htmlTagName();
      setState(93);
      match(HTMLParser::TAG_CLOSE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(95);
      match(HTMLParser::TAG_OPEN);
      setState(96);
      htmlTagName();
      setState(100);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HTMLParser::TAG_NAME) {
        setState(97);
        htmlAttribute();
        setState(102);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(103);
      match(HTMLParser::TAG_SLASH_CLOSE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(105);
      match(HTMLParser::TAG_OPEN);
      setState(106);
      htmlTagName();
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HTMLParser::TAG_NAME) {
        setState(107);
        htmlAttribute();
        setState(112);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(113);
      match(HTMLParser::TAG_CLOSE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(115);
      scriptlet();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(116);
      script();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(117);
      style();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlContentContext ------------------------------------------------------------------

HTMLParser::HtmlContentContext::HtmlContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HTMLParser::HtmlChardataContext *> HTMLParser::HtmlContentContext::htmlChardata() {
  return getRuleContexts<HTMLParser::HtmlChardataContext>();
}

HTMLParser::HtmlChardataContext* HTMLParser::HtmlContentContext::htmlChardata(size_t i) {
  return getRuleContext<HTMLParser::HtmlChardataContext>(i);
}

std::vector<HTMLParser::HtmlElementContext *> HTMLParser::HtmlContentContext::htmlElement() {
  return getRuleContexts<HTMLParser::HtmlElementContext>();
}

HTMLParser::HtmlElementContext* HTMLParser::HtmlContentContext::htmlElement(size_t i) {
  return getRuleContext<HTMLParser::HtmlElementContext>(i);
}

std::vector<HTMLParser::XhtmlCDATAContext *> HTMLParser::HtmlContentContext::xhtmlCDATA() {
  return getRuleContexts<HTMLParser::XhtmlCDATAContext>();
}

HTMLParser::XhtmlCDATAContext* HTMLParser::HtmlContentContext::xhtmlCDATA(size_t i) {
  return getRuleContext<HTMLParser::XhtmlCDATAContext>(i);
}

std::vector<HTMLParser::HtmlCommentContext *> HTMLParser::HtmlContentContext::htmlComment() {
  return getRuleContexts<HTMLParser::HtmlCommentContext>();
}

HTMLParser::HtmlCommentContext* HTMLParser::HtmlContentContext::htmlComment(size_t i) {
  return getRuleContext<HTMLParser::HtmlCommentContext>(i);
}


size_t HTMLParser::HtmlContentContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlContent;
}

void HTMLParser::HtmlContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlContent(this);
}

void HTMLParser::HtmlContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlContent(this);
}

HTMLParser::HtmlContentContext* HTMLParser::htmlContent() {
  HtmlContentContext *_localctx = _tracker.createInstance<HtmlContentContext>(_ctx, getState());
  enterRule(_localctx, 6, HTMLParser::RuleHtmlContent);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HTMLParser::SEA_WS

    || _la == HTMLParser::HTML_TEXT) {
      setState(120);
      htmlChardata();
    }
    setState(133);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(126);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case HTMLParser::SCRIPTLET:
          case HTMLParser::SCRIPT_OPEN:
          case HTMLParser::STYLE_OPEN:
          case HTMLParser::TAG_OPEN: {
            setState(123);
            htmlElement();
            break;
          }

          case HTMLParser::CDATA: {
            setState(124);
            xhtmlCDATA();
            break;
          }

          case HTMLParser::HTML_COMMENT:
          case HTMLParser::HTML_CONDITIONAL_COMMENT: {
            setState(125);
            htmlComment();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(129);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HTMLParser::SEA_WS

        || _la == HTMLParser::HTML_TEXT) {
          setState(128);
          htmlChardata();
        } 
      }
      setState(135);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlAttributeContext ------------------------------------------------------------------

HTMLParser::HtmlAttributeContext::HtmlAttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HTMLParser::HtmlAttributeNameContext* HTMLParser::HtmlAttributeContext::htmlAttributeName() {
  return getRuleContext<HTMLParser::HtmlAttributeNameContext>(0);
}

tree::TerminalNode* HTMLParser::HtmlAttributeContext::TAG_EQUALS() {
  return getToken(HTMLParser::TAG_EQUALS, 0);
}

HTMLParser::HtmlAttributeValueContext* HTMLParser::HtmlAttributeContext::htmlAttributeValue() {
  return getRuleContext<HTMLParser::HtmlAttributeValueContext>(0);
}


size_t HTMLParser::HtmlAttributeContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlAttribute;
}

void HTMLParser::HtmlAttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlAttribute(this);
}

void HTMLParser::HtmlAttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlAttribute(this);
}

HTMLParser::HtmlAttributeContext* HTMLParser::htmlAttribute() {
  HtmlAttributeContext *_localctx = _tracker.createInstance<HtmlAttributeContext>(_ctx, getState());
  enterRule(_localctx, 8, HTMLParser::RuleHtmlAttribute);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(136);
      htmlAttributeName();
      setState(137);
      match(HTMLParser::TAG_EQUALS);
      setState(138);
      htmlAttributeValue();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      htmlAttributeName();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlAttributeNameContext ------------------------------------------------------------------

HTMLParser::HtmlAttributeNameContext::HtmlAttributeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::HtmlAttributeNameContext::TAG_NAME() {
  return getToken(HTMLParser::TAG_NAME, 0);
}


size_t HTMLParser::HtmlAttributeNameContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlAttributeName;
}

void HTMLParser::HtmlAttributeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlAttributeName(this);
}

void HTMLParser::HtmlAttributeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlAttributeName(this);
}

HTMLParser::HtmlAttributeNameContext* HTMLParser::htmlAttributeName() {
  HtmlAttributeNameContext *_localctx = _tracker.createInstance<HtmlAttributeNameContext>(_ctx, getState());
  enterRule(_localctx, 10, HTMLParser::RuleHtmlAttributeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(HTMLParser::TAG_NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlAttributeValueContext ------------------------------------------------------------------

HTMLParser::HtmlAttributeValueContext::HtmlAttributeValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::HtmlAttributeValueContext::ATTVALUE_VALUE() {
  return getToken(HTMLParser::ATTVALUE_VALUE, 0);
}


size_t HTMLParser::HtmlAttributeValueContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlAttributeValue;
}

void HTMLParser::HtmlAttributeValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlAttributeValue(this);
}

void HTMLParser::HtmlAttributeValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlAttributeValue(this);
}

HTMLParser::HtmlAttributeValueContext* HTMLParser::htmlAttributeValue() {
  HtmlAttributeValueContext *_localctx = _tracker.createInstance<HtmlAttributeValueContext>(_ctx, getState());
  enterRule(_localctx, 12, HTMLParser::RuleHtmlAttributeValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(HTMLParser::ATTVALUE_VALUE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlTagNameContext ------------------------------------------------------------------

HTMLParser::HtmlTagNameContext::HtmlTagNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::HtmlTagNameContext::TAG_NAME() {
  return getToken(HTMLParser::TAG_NAME, 0);
}


size_t HTMLParser::HtmlTagNameContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlTagName;
}

void HTMLParser::HtmlTagNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlTagName(this);
}

void HTMLParser::HtmlTagNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlTagName(this);
}

HTMLParser::HtmlTagNameContext* HTMLParser::htmlTagName() {
  HtmlTagNameContext *_localctx = _tracker.createInstance<HtmlTagNameContext>(_ctx, getState());
  enterRule(_localctx, 14, HTMLParser::RuleHtmlTagName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(HTMLParser::TAG_NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlChardataContext ------------------------------------------------------------------

HTMLParser::HtmlChardataContext::HtmlChardataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::HtmlChardataContext::HTML_TEXT() {
  return getToken(HTMLParser::HTML_TEXT, 0);
}

tree::TerminalNode* HTMLParser::HtmlChardataContext::SEA_WS() {
  return getToken(HTMLParser::SEA_WS, 0);
}


size_t HTMLParser::HtmlChardataContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlChardata;
}

void HTMLParser::HtmlChardataContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlChardata(this);
}

void HTMLParser::HtmlChardataContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlChardata(this);
}

HTMLParser::HtmlChardataContext* HTMLParser::htmlChardata() {
  HtmlChardataContext *_localctx = _tracker.createInstance<HtmlChardataContext>(_ctx, getState());
  enterRule(_localctx, 16, HTMLParser::RuleHtmlChardata);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    _la = _input->LA(1);
    if (!(_la == HTMLParser::SEA_WS

    || _la == HTMLParser::HTML_TEXT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlMiscContext ------------------------------------------------------------------

HTMLParser::HtmlMiscContext::HtmlMiscContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HTMLParser::HtmlCommentContext* HTMLParser::HtmlMiscContext::htmlComment() {
  return getRuleContext<HTMLParser::HtmlCommentContext>(0);
}

tree::TerminalNode* HTMLParser::HtmlMiscContext::SEA_WS() {
  return getToken(HTMLParser::SEA_WS, 0);
}


size_t HTMLParser::HtmlMiscContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlMisc;
}

void HTMLParser::HtmlMiscContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlMisc(this);
}

void HTMLParser::HtmlMiscContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlMisc(this);
}

HTMLParser::HtmlMiscContext* HTMLParser::htmlMisc() {
  HtmlMiscContext *_localctx = _tracker.createInstance<HtmlMiscContext>(_ctx, getState());
  enterRule(_localctx, 18, HTMLParser::RuleHtmlMisc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(153);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HTMLParser::HTML_COMMENT:
      case HTMLParser::HTML_CONDITIONAL_COMMENT: {
        enterOuterAlt(_localctx, 1);
        setState(151);
        htmlComment();
        break;
      }

      case HTMLParser::SEA_WS: {
        enterOuterAlt(_localctx, 2);
        setState(152);
        match(HTMLParser::SEA_WS);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HtmlCommentContext ------------------------------------------------------------------

HTMLParser::HtmlCommentContext::HtmlCommentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::HtmlCommentContext::HTML_COMMENT() {
  return getToken(HTMLParser::HTML_COMMENT, 0);
}

tree::TerminalNode* HTMLParser::HtmlCommentContext::HTML_CONDITIONAL_COMMENT() {
  return getToken(HTMLParser::HTML_CONDITIONAL_COMMENT, 0);
}


size_t HTMLParser::HtmlCommentContext::getRuleIndex() const {
  return HTMLParser::RuleHtmlComment;
}

void HTMLParser::HtmlCommentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHtmlComment(this);
}

void HTMLParser::HtmlCommentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHtmlComment(this);
}

HTMLParser::HtmlCommentContext* HTMLParser::htmlComment() {
  HtmlCommentContext *_localctx = _tracker.createInstance<HtmlCommentContext>(_ctx, getState());
  enterRule(_localctx, 20, HTMLParser::RuleHtmlComment);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _la = _input->LA(1);
    if (!(_la == HTMLParser::HTML_COMMENT

    || _la == HTMLParser::HTML_CONDITIONAL_COMMENT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- XhtmlCDATAContext ------------------------------------------------------------------

HTMLParser::XhtmlCDATAContext::XhtmlCDATAContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::XhtmlCDATAContext::CDATA() {
  return getToken(HTMLParser::CDATA, 0);
}


size_t HTMLParser::XhtmlCDATAContext::getRuleIndex() const {
  return HTMLParser::RuleXhtmlCDATA;
}

void HTMLParser::XhtmlCDATAContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXhtmlCDATA(this);
}

void HTMLParser::XhtmlCDATAContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXhtmlCDATA(this);
}

HTMLParser::XhtmlCDATAContext* HTMLParser::xhtmlCDATA() {
  XhtmlCDATAContext *_localctx = _tracker.createInstance<XhtmlCDATAContext>(_ctx, getState());
  enterRule(_localctx, 22, HTMLParser::RuleXhtmlCDATA);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    match(HTMLParser::CDATA);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DtdContext ------------------------------------------------------------------

HTMLParser::DtdContext::DtdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::DtdContext::DTD() {
  return getToken(HTMLParser::DTD, 0);
}


size_t HTMLParser::DtdContext::getRuleIndex() const {
  return HTMLParser::RuleDtd;
}

void HTMLParser::DtdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDtd(this);
}

void HTMLParser::DtdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDtd(this);
}

HTMLParser::DtdContext* HTMLParser::dtd() {
  DtdContext *_localctx = _tracker.createInstance<DtdContext>(_ctx, getState());
  enterRule(_localctx, 24, HTMLParser::RuleDtd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    match(HTMLParser::DTD);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- XmlContext ------------------------------------------------------------------

HTMLParser::XmlContext::XmlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::XmlContext::XML_DECLARATION() {
  return getToken(HTMLParser::XML_DECLARATION, 0);
}


size_t HTMLParser::XmlContext::getRuleIndex() const {
  return HTMLParser::RuleXml;
}

void HTMLParser::XmlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXml(this);
}

void HTMLParser::XmlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXml(this);
}

HTMLParser::XmlContext* HTMLParser::xml() {
  XmlContext *_localctx = _tracker.createInstance<XmlContext>(_ctx, getState());
  enterRule(_localctx, 26, HTMLParser::RuleXml);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(HTMLParser::XML_DECLARATION);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptletContext ------------------------------------------------------------------

HTMLParser::ScriptletContext::ScriptletContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::ScriptletContext::SCRIPTLET() {
  return getToken(HTMLParser::SCRIPTLET, 0);
}


size_t HTMLParser::ScriptletContext::getRuleIndex() const {
  return HTMLParser::RuleScriptlet;
}

void HTMLParser::ScriptletContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptlet(this);
}

void HTMLParser::ScriptletContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptlet(this);
}

HTMLParser::ScriptletContext* HTMLParser::scriptlet() {
  ScriptletContext *_localctx = _tracker.createInstance<ScriptletContext>(_ctx, getState());
  enterRule(_localctx, 28, HTMLParser::RuleScriptlet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    match(HTMLParser::SCRIPTLET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptContext ------------------------------------------------------------------

HTMLParser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::ScriptContext::SCRIPT_OPEN() {
  return getToken(HTMLParser::SCRIPT_OPEN, 0);
}

tree::TerminalNode* HTMLParser::ScriptContext::SCRIPT_BODY() {
  return getToken(HTMLParser::SCRIPT_BODY, 0);
}

tree::TerminalNode* HTMLParser::ScriptContext::SCRIPT_SHORT_BODY() {
  return getToken(HTMLParser::SCRIPT_SHORT_BODY, 0);
}


size_t HTMLParser::ScriptContext::getRuleIndex() const {
  return HTMLParser::RuleScript;
}

void HTMLParser::ScriptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScript(this);
}

void HTMLParser::ScriptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScript(this);
}

HTMLParser::ScriptContext* HTMLParser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 30, HTMLParser::RuleScript);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    match(HTMLParser::SCRIPT_OPEN);
    setState(166);
    _la = _input->LA(1);
    if (!(_la == HTMLParser::SCRIPT_BODY

    || _la == HTMLParser::SCRIPT_SHORT_BODY)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleContext ------------------------------------------------------------------

HTMLParser::StyleContext::StyleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HTMLParser::StyleContext::STYLE_OPEN() {
  return getToken(HTMLParser::STYLE_OPEN, 0);
}

tree::TerminalNode* HTMLParser::StyleContext::STYLE_BODY() {
  return getToken(HTMLParser::STYLE_BODY, 0);
}

tree::TerminalNode* HTMLParser::StyleContext::STYLE_SHORT_BODY() {
  return getToken(HTMLParser::STYLE_SHORT_BODY, 0);
}


size_t HTMLParser::StyleContext::getRuleIndex() const {
  return HTMLParser::RuleStyle;
}

void HTMLParser::StyleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyle(this);
}

void HTMLParser::StyleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HTMLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyle(this);
}

HTMLParser::StyleContext* HTMLParser::style() {
  StyleContext *_localctx = _tracker.createInstance<StyleContext>(_ctx, getState());
  enterRule(_localctx, 32, HTMLParser::RuleStyle);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(HTMLParser::STYLE_OPEN);
    setState(169);
    _la = _input->LA(1);
    if (!(_la == HTMLParser::STYLE_BODY

    || _la == HTMLParser::STYLE_SHORT_BODY)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> HTMLParser::_decisionToDFA;
atn::PredictionContextCache HTMLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HTMLParser::_atn;
std::vector<uint16_t> HTMLParser::_serializedATN;

std::vector<std::string> HTMLParser::_ruleNames = {
  "htmlDocument", "htmlElements", "htmlElement", "htmlContent", "htmlAttribute", 
  "htmlAttributeName", "htmlAttributeValue", "htmlTagName", "htmlChardata", 
  "htmlMisc", "htmlComment", "xhtmlCDATA", "dtd", "xml", "scriptlet", "script", 
  "style"
};

std::vector<std::string> HTMLParser::_literalNames = {
  "", "", "", "", "", "", "", "", "", "", "'<'", "", "'>'", "'/>'", "'/'", 
  "'='"
};

std::vector<std::string> HTMLParser::_symbolicNames = {
  "", "HTML_COMMENT", "HTML_CONDITIONAL_COMMENT", "XML_DECLARATION", "CDATA", 
  "DTD", "SCRIPTLET", "SEA_WS", "SCRIPT_OPEN", "STYLE_OPEN", "TAG_OPEN", 
  "HTML_TEXT", "TAG_CLOSE", "TAG_SLASH_CLOSE", "TAG_SLASH", "TAG_EQUALS", 
  "TAG_NAME", "TAG_WHITESPACE", "SCRIPT_BODY", "SCRIPT_SHORT_BODY", "STYLE_BODY", 
  "STYLE_SHORT_BODY", "ATTVALUE_VALUE", "ATTRIBUTE"
};

dfa::Vocabulary HTMLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> HTMLParser::_tokenNames;

HTMLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x19, 0xae, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x27, 0xa, 0x2, 0xc, 0x2, 0xe, 
    0x2, 0x2a, 0xb, 0x2, 0x3, 0x2, 0x5, 0x2, 0x2d, 0xa, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x7, 0x2, 0x31, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x34, 0xb, 0x2, 0x3, 
    0x2, 0x5, 0x2, 0x37, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x3b, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x3e, 0xb, 0x2, 0x3, 0x2, 0x7, 0x2, 0x41, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x44, 0xb, 0x2, 0x3, 0x3, 0x7, 0x3, 0x47, 0xa, 
    0x3, 0xc, 0x3, 0xe, 0x3, 0x4a, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 
    0x4e, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x51, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x7, 0x4, 0x56, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x59, 0xb, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x65, 0xa, 0x4, 0xc, 0x4, 0xe, 
    0x4, 0x68, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x7, 0x4, 0x6f, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x72, 0xb, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x79, 0xa, 0x4, 0x3, 
    0x5, 0x5, 0x5, 0x7c, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 
    0x81, 0xa, 0x5, 0x3, 0x5, 0x5, 0x5, 0x84, 0xa, 0x5, 0x7, 0x5, 0x86, 
    0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x89, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x90, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x5, 0xb, 0x9c, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x2, 0x2, 0x13, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x2, 0x6, 0x4, 0x2, 0x9, 0x9, 
    0xd, 0xd, 0x3, 0x2, 0x3, 0x4, 0x3, 0x2, 0x14, 0x15, 0x3, 0x2, 0x16, 
    0x17, 0x2, 0xb6, 0x2, 0x28, 0x3, 0x2, 0x2, 0x2, 0x4, 0x48, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x78, 0x3, 0x2, 0x2, 0x2, 0x8, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x8f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x91, 0x3, 0x2, 0x2, 0x2, 0xe, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x95, 0x3, 0x2, 0x2, 0x2, 0x12, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x16, 0x9d, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xa1, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x22, 0xaa, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x27, 0x5, 0x1e, 0x10, 0x2, 0x25, 0x27, 0x7, 0x9, 0x2, 0x2, 0x26, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x26, 0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x2a, 0x3, 
    0x2, 0x2, 0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0x29, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 
    0x2, 0x2b, 0x2d, 0x5, 0x1c, 0xf, 0x2, 0x2c, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x32, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x31, 0x5, 0x1e, 0x10, 0x2, 0x2f, 0x31, 0x7, 0x9, 0x2, 0x2, 0x30, 0x2e, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x35, 0x37, 0x5, 0x1a, 0xe, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 0x37, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x38, 
    0x3b, 0x5, 0x1e, 0x10, 0x2, 0x39, 0x3b, 0x7, 0x9, 0x2, 0x2, 0x3a, 0x38, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3e, 0x3, 
    0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0x3d, 0x42, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 
    0x2, 0x3f, 0x41, 0x5, 0x4, 0x3, 0x2, 0x40, 0x3f, 0x3, 0x2, 0x2, 0x2, 
    0x41, 0x44, 0x3, 0x2, 0x2, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 0x2, 0x42, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x43, 0x3, 0x3, 0x2, 0x2, 0x2, 0x44, 0x42, 
    0x3, 0x2, 0x2, 0x2, 0x45, 0x47, 0x5, 0x14, 0xb, 0x2, 0x46, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x47, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 
    0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4f, 0x5, 0x6, 0x4, 0x2, 
    0x4c, 0x4e, 0x5, 0x14, 0xb, 0x2, 0x4d, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 
    0x3, 0x2, 0x2, 0x2, 0x50, 0x5, 0x3, 0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0xc, 0x2, 0x2, 0x53, 0x57, 0x5, 0x10, 
    0x9, 0x2, 0x54, 0x56, 0x5, 0xa, 0x6, 0x2, 0x55, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x59, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 
    0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x59, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0xe, 0x2, 0x2, 0x5b, 0x5c, 
    0x5, 0x8, 0x5, 0x2, 0x5c, 0x5d, 0x7, 0xc, 0x2, 0x2, 0x5d, 0x5e, 0x7, 
    0x10, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0x10, 0x9, 0x2, 0x5f, 0x60, 0x7, 0xe, 
    0x2, 0x2, 0x60, 0x79, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x7, 0xc, 0x2, 
    0x2, 0x62, 0x66, 0x5, 0x10, 0x9, 0x2, 0x63, 0x65, 0x5, 0xa, 0x6, 0x2, 
    0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0x68, 0x3, 0x2, 0x2, 0x2, 0x66, 
    0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 0x69, 
    0x3, 0x2, 0x2, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x7, 
    0xf, 0x2, 0x2, 0x6a, 0x79, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0xc, 
    0x2, 0x2, 0x6c, 0x70, 0x5, 0x10, 0x9, 0x2, 0x6d, 0x6f, 0x5, 0xa, 0x6, 
    0x2, 0x6e, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x72, 0x3, 0x2, 0x2, 0x2, 
    0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x3, 0x2, 0x2, 0x2, 0x71, 
    0x73, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 
    0x7, 0xe, 0x2, 0x2, 0x74, 0x79, 0x3, 0x2, 0x2, 0x2, 0x75, 0x79, 0x5, 
    0x1e, 0x10, 0x2, 0x76, 0x79, 0x5, 0x20, 0x11, 0x2, 0x77, 0x79, 0x5, 
    0x22, 0x12, 0x2, 0x78, 0x52, 0x3, 0x2, 0x2, 0x2, 0x78, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x78, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x78, 0x75, 0x3, 0x2, 0x2, 
    0x2, 0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x77, 0x3, 0x2, 0x2, 0x2, 
    0x79, 0x7, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7c, 0x5, 0x12, 0xa, 0x2, 0x7b, 
    0x7a, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x87, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x81, 0x5, 0x6, 0x4, 0x2, 0x7e, 0x81, 0x5, 
    0x18, 0xd, 0x2, 0x7f, 0x81, 0x5, 0x16, 0xc, 0x2, 0x80, 0x7d, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7f, 0x3, 0x2, 0x2, 
    0x2, 0x81, 0x83, 0x3, 0x2, 0x2, 0x2, 0x82, 0x84, 0x5, 0x12, 0xa, 0x2, 
    0x83, 0x82, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0x85, 0x80, 0x3, 0x2, 0x2, 0x2, 0x86, 0x89, 
    0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x88, 0x9, 0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 0x3, 0x2, 
    0x2, 0x2, 0x8a, 0x8b, 0x5, 0xc, 0x7, 0x2, 0x8b, 0x8c, 0x7, 0x11, 0x2, 
    0x2, 0x8c, 0x8d, 0x5, 0xe, 0x8, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 0x2, 
    0x8e, 0x90, 0x5, 0xc, 0x7, 0x2, 0x8f, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8f, 
    0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 0xb, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 
    0x7, 0x12, 0x2, 0x2, 0x92, 0xd, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 
    0x18, 0x2, 0x2, 0x94, 0xf, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x7, 0x12, 
    0x2, 0x2, 0x96, 0x11, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x9, 0x2, 0x2, 
    0x2, 0x98, 0x13, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9c, 0x5, 0x16, 0xc, 0x2, 
    0x9a, 0x9c, 0x7, 0x9, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x15, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 
    0x9, 0x3, 0x2, 0x2, 0x9e, 0x17, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 0x7, 
    0x6, 0x2, 0x2, 0xa0, 0x19, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x7, 0x7, 
    0x2, 0x2, 0xa2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x7, 0x5, 0x2, 
    0x2, 0xa4, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x7, 0x8, 0x2, 0x2, 
    0xa6, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x7, 0xa, 0x2, 0x2, 0xa8, 
    0xa9, 0x9, 0x4, 0x2, 0x2, 0xa9, 0x21, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 
    0x7, 0xb, 0x2, 0x2, 0xab, 0xac, 0x9, 0x5, 0x2, 0x2, 0xac, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0x17, 0x26, 0x28, 0x2c, 0x30, 0x32, 0x36, 0x3a, 0x3c, 
    0x42, 0x48, 0x4f, 0x57, 0x66, 0x70, 0x78, 0x7b, 0x80, 0x83, 0x87, 0x8f, 
    0x9b, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

HTMLParser::Initializer HTMLParser::_init;

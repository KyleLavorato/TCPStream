
// Generated from HTMLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  HTMLLexer : public antlr4::Lexer {
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
    TAG = 1, SCRIPT = 2, STYLE = 3, ATTVALUE = 4
  };

  HTMLLexer(antlr4::CharStream *input);
  ~HTMLLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};


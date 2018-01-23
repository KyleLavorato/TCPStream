grammar HTTP;

generic-message
:
	start-line (message-header CRLF)* CRLF [message-body]
;

start-line
:
	Request-Line
	| Status-Line
;

message-header
:
	field-name ':' [field-value]
;

field-name
:
	token
;

field-value
:
	(field-content | LWS)*
;

field-content
:
	TEXT*
	| other-content*
;

other-content
:
	token
	| separators
	| quoted-string
;

CRLF
:
	CR LF
;

message-body
:
	entity-body
	| Transfer-Encoding
;
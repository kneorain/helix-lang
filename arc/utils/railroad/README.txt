RR - Railroad Diagram Generator

  version 2.1
  released Jan 06, 2024
  from https://www.bottlecaps.de/rr

Usage: java -jar rr.war {OPTION}... GRAMMAR
    or java -jar rr.war -gui [-port:PORT]

  Options:

  -suppressebnf    do not show EBNF next to generated diagrams
  -keeprecursion   no direct recursion elimination
  -nofactoring     no left or right factoring
  -noinline        do not inline nonterminals that derive to single literals
  -noepsilon       remove nonterminal references that derive to epsilon only
  -color:COLOR     use COLOR as base color, pattern: #[0-9a-fA-F]{6}
  -offset:OFFSET   hue offset to secondary color in degrees
  -html            create HTML output, rather than XHTML
  -md              create Markdown output, rather than XHTML
  -png             create PNG graphics, rather than SVG
  -noembedded      create text and graphics in separate files in a zip, rather than embedded graphics
  -out:FILE        create FILE, rather than writing result to standard output
  -width:PIXELS    try to break graphics into multiple lines, when width exceeds PIXELS (default 992)
  -enc:ENCODING    set grammar input encoding (default: autodetect UTF8/16 or use system encoding)

  GRAMMAR          path of grammar, in W3C style EBNF (use '-' for stdin)

  -gui             run GUI on http://localhost:8080/
  -port:PORT       use PORT rather than 8080

rr.war is an executable war file. It can be run with "java -jar" as shown
above, but it can also be deployed in servlet containers like Tomcat or Jetty.

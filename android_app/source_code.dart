import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:flutter_syntax_view/flutter_syntax_view.dart';
import 'code.dart';

class SourceCode extends StatelessWidget{

@override Widget build(BuildContext bc){
return Scaffold(appBar: AppBar(title: Text('source code')),
body:SingleChildScrollView(child: Center(

child: SyntaxView(code: code, syntax: Syntax.DART,
syntaxTheme: SyntaxTheme.vscodeDark(), fontSize: 12.0,
withZoom: true, withLinesCount: true, expanded: false,
selectable: true)


)));}}



import 'package:flutter/material.dart';
import './home.dart';
import './intro.dart';
import './globals.dart';

void main()async {
  WidgetsFlutterBinding.ensureInitialized();
  await isFirstTime();
  runApp(MainApp());}

class MainApp extends StatelessWidget {
MainApp({super.key});

@override Widget build(BuildContext context) {
return MaterialApp(
  debugShowCheckedModeBanner: false,
  //primaryIconTheme: IconThemeData(color: Colors.black),
  title: 'ble lora',
  home: !firstTime ? Home() : Intro());}}

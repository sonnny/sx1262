import 'package:flutter/material.dart';
import 'package:get/get.dart';
import './home.dart';

void main() {runApp(MainApp());}

class MainApp extends StatelessWidget {
  MainApp({super.key});

  @override Widget build(BuildContext context) {
    return GetMaterialApp(
      debugShowCheckedModeBanner: false,
      darkTheme: ThemeData.dark(),
      themeMode: ThemeMode.system,
      home: Home());}}


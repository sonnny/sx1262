import 'package:flutter/material.dart';

import 'package:shared_preferences/shared_preferences.dart';

const String APP_NAME = "Ble lora";
const String BLE_ADDRESS = '9C:1D:58:0F:3B:D8';
const String SERVICE     = 'FFE0';
const String TX_CHAR     = 'FFE1';

const List<int> FW4   = [0x46,0x57,0x34,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 4
const List<int> FW3   = [0x46,0x57,0x33,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 3
const List<int> FW2   = [0x46,0x57,0x32,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 2
const List<int> FW1   = [0x46,0x57,0x31,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 1
const List<int> STOP  = [0x53,0x54,0x4F,0x50,0x20, 0x41,0x42,0x20,0x20, 0x0D];//stop
const List<int> BACK  = [0x42,0x41,0x43,0x4B,0x20, 0x41,0x42,0x20,0x20, 0x0D];
const List<int> LEFT  = [0x4C,0x45,0x46,0x54,0x20, 0x41,0x42,0x20,0x20, 0x0D];
const List<int> RIGHT = [0x52,0x49,0x47,0x48,0x54,0x20, 0x41,0x42,0x20,0x20, 0x0D];

TextStyle connectedStyle = TextStyle(
color:Colors.green,fontSize:18,
fontWeight:FontWeight.bold);

TextStyle notConnectedStyle = TextStyle(color:Colors.red);

TextStyle forwardStyle = TextStyle(
color: Colors.blue, fontSize: 24,
fontWeight: FontWeight.bold);

SharedPreferences? sharedPreferences;
bool firstTime = true;

initSharedPrefs() async {
  if (sharedPreferences == null)
    sharedPreferences = await SharedPreferences.getInstance();
}

isFirstTime() async {
  await initSharedPrefs();
  if (sharedPreferences!.containsKey("firstTime")) {
    print("isFirstTime: false");
    firstTime = false;
  } else {
    print("isFirstTime: true");
    sharedPreferences!.setBool("firstTime", false);
    firstTime = true;
  }
}

bool isFullScreen(Size currentSize, Size fullSize) {
  if (currentSize.height == fullSize.height &&
      fullSize.width == currentSize.width)
    return true;
  else
    return false;
}

Size getSize(BuildContext context) {
  return Size(
      MediaQuery.of(context).size.width, MediaQuery.of(context).size.height);
}

double getHeight(BuildContext context) {
  return MediaQuery.of(context).size.height;
}

double getWidth(BuildContext context) {
  return MediaQuery.of(context).size.width;
}

const String code = r"""

///////////////main.dart
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

///////////////ble_controller.dart
import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:get/get.dart';

const String BLE_ADDRESS = '9C:1D:58:0F:3B:D8';
const String SERVICE     = 'FFE0';
const String TX_CHAR     = 'FFE1';

const List<int> FW4    = [0x46,0x57,0x34,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 4
const List<int> FW3    = [0x46,0x57,0x33,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 3
const List<int> FW2    = [0x46,0x57,0x32,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 2
const List<int> FW1    = [0x46,0x57,0x31,0x20, 0x41,0x42,0x20,0x20, 0x0D];     //forward speed 1
const List<int> STOP   = [0x53,0x54,0x4F,0x50,0x20, 0x41,0x42,0x20,0x20, 0x0D];//stop
const List<int> BACK   = [0x42,0x41,0x43,0x4B,0x20, 0x41,0x42,0x20,0x20, 0x0D];//BACK
const List<int> LEFT   = [0x4C,0x45,0x46,0x54,0x20, 0x41,0x42,0x20,0x20, 0x0D];//LEFT
const List<int> RIGHT  = [0x52,0x49,0x47,0x48,0x54,0x20, 0x41,0x42,0x20,0x20, 0x0D];//RIGHT
const List<int> CENTER = [0x43,0x45,0x4E,0x54,0x45,0x52, 0x20, 0x41,0x42, 0x20,0x20, 0x0D];//CENTER


class BleController extends GetxController{

var status = 'connect...'.obs;
var tx;
late BluetoothDevice device;  

//connect function  
void connect() async {
device = BluetoothDevice(
remoteId: DeviceIdentifier(BLE_ADDRESS));
await device.connect(); //connect without bluetooth scan
List<BluetoothService> services = await device.discoverServices();
tx = BluetoothCharacteristic(remoteId: device.remoteId,
serviceUuid: Guid(SERVICE),
characteristicUuid: Guid(TX_CHAR));
status.value = 'ready';}

void send(List<int> data) async {
try{await tx.write(data, withoutResponse: true);} catch(e){}}

void disconnect() async { device.disconnect(); }
  
}
////////////////////my_dialog.dart
import 'package:flutter/material.dart';

class MyDialog extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Dialog(
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(5.0)),
      child: Padding(
        padding: const EdgeInsets.all(8.0),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Padding(
              padding: const EdgeInsets.all(20.0),
              child: Text(
             
"Make sure your phone's bluetooth is on\nAdd location in AndroidManifest.xml\nGo to settings then allow this app \nlocation permission \nCheckout flutter_blue_plus plugin\nfor more info on the manifest file\nuse the switch to reverse rudder direction",
                
                textAlign: TextAlign.center,
              ),
            ),
            GestureDetector(
              onTap: () {
                Navigator.pop(context);
              },
              child: Container(
                child: Center(
                  child: Text(
                    "OK",
                    style: TextStyle(
                        color: Colors.green, fontWeight: FontWeight.w800),
                  ),
                ),
                width: MediaQuery.of(context).size.width * 0.6,
                height: MediaQuery.of(context).size.height * 0.045,
                decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(5.0),
                  border: Border.all(color: Colors.green),
                  color: Colors.transparent,
                ),
              ),
            ),
            SizedBox(height: 10),
          ],
        ),
      ),
    );
  }
}
/////////////////////switch_controller.dart
import 'package:flutter/material.dart';
import 'package:get/get.dart';

class SwitchController extends GetxController{
  var isSwitched = false.obs;
  
  void toggleSwitch(bool value) {
  
    isSwitched.value = value;}}
///////////////////home.dart
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:get/get.dart';
import './ble_controller.dart';
import './my_dialog.dart';
import './switch_controller.dart';
import './source_code.dart';

TextStyle connectedStyle = TextStyle(
color:Colors.green,fontSize: 26,
fontWeight:FontWeight.bold);

TextStyle notConnectedStyle = TextStyle(color:Colors.red);

TextStyle forwardStyle = TextStyle(
color: Colors.blue, fontSize: 30,
fontWeight: FontWeight.bold);

class Home extends StatelessWidget{

final ble = Get.put(BleController());
  
@override Widget build(BuildContext context){
final SwitchController switchController = Get.put(SwitchController());
return Scaffold(

// scaffold appbar
appBar: AppBar(
backgroundColor: Colors.transparent,
elevation: 0,
title: Text('ble rc boat'),
actions: [

Obx(() => Switch(value: switchController.isSwitched.value,
onChanged: (value) {switchController.toggleSwitch(value);})),

SizedBox(width:20.0),

IconButton(icon: Icon(Icons.help, color: Colors.purple),
onPressed:(){ showDialog(context: context,
  builder: (context) => MyDialog());}),

SizedBox(width:20.0),

IconButton(icon: Icon(Icons.lightbulb), onPressed:(){
Get.isDarkMode ? Get.changeThemeMode(ThemeMode.light)
               : Get.changeThemeMode(ThemeMode.dark);})
  
]),
 
// scaffold body column    
body: Column(spacing: 30, mainAxisAlignment: MainAxisAlignment.center,
  children: [
     
//1st row
GetX<BleController>(
builder:(_) { return Row( mainAxisAlignment: MainAxisAlignment.spaceAround, 
children: [ 
Text('address: ${BLE_ADDRESS}'),
ElevatedButton(child: Text('${ble.status}',
style: (ble.status == 'ready') ? connectedStyle : 
notConnectedStyle), onPressed:() => ble.connect())
]);}),

//2nd row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
children: [
  ElevatedButton(child: Text('<<<<',style: forwardStyle), onPressed:(){ ble.send(FW4);}),
  ElevatedButton(child: Text('<<<',style: forwardStyle), onPressed:(){  ble.send(FW3);}),
  ElevatedButton(child: Text('<<',style: forwardStyle), onPressed:(){   ble.send(FW2);}),
  ElevatedButton(child: Text('<', style: forwardStyle), onPressed:(){   ble.send(FW1);})]),
  
//3rd row
IconButton(iconSize: 75, onPressed:(){ ble.send(STOP);},
icon: Icon(Icons.hexagon, color: Colors.red)),
  
//4th row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
children: [

IconButton(iconSize: 75, onPressed:(){ if (switchController.isSwitched.value) {ble.send(LEFT);} else {ble.send(RIGHT);}},
icon: Icon(Icons.arrow_back_rounded)),

IconButton(iconSize: 75, onPressed:(){ ble.send(CENTER);},
icon: Icon(Icons.compare_arrows)),
    
IconButton(iconSize: 75, onPressed:(){ if (switchController.isSwitched.value) {ble.send(RIGHT);} else {ble.send(LEFT);}},
icon: Icon(Icons.arrow_forward_rounded)),
    
]),

// 5th row
IconButton(iconSize: 75, onPressed:(){ ble.send(BACK);},
icon: Icon(Icons.arrow_circle_down)),
    
//6th row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
children: [

IconButton(iconSize: 40, onPressed:(){Get.to(() => SourceCode());}
icon: Icon(Icons.comment)),


IconButton(iconSize: 50, onPressed:() async {
  ble.send(STOP);
  ble.send(CENTER);
  ble.disconnect();
  SystemNavigator.pop();},
  icon: Icon(Icons.power_settings_new))
  
])      
        
]));}}
///////////////////
""";

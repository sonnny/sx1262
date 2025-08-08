import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:get/get.dart';
import './ble_controller.dart';
import './my_dialog.dart';

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
return Scaffold(

// scaffold appbar
appBar: AppBar(
backgroundColor: Colors.transparent,
elevation: 0,
title: Text('ble rc boat'),
actions: [

// first icon on the app bar
IconButton(icon: Icon(Icons.help, color: Colors.purple),
onPressed:(){ showDialog(context: context,
  builder: (context) => MyDialog());}),
  
// second icon on the app bar
IconButton(icon: Icon(Icons.power_settings_new, color: Colors.teal),
onPressed:() async { ble.send(STOP); ble.send(CENTER); ble.disconnect();
  SystemNavigator.pop();})
  
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
  IconButton(iconSize: 75, onPressed:(){ ble.send(LEFT);},
    icon: Icon(Icons.arrow_back_rounded)),
  IconButton(iconSize: 75, onPressed:(){ ble.send(CENTER);},
    icon: Icon(Icons.compare_arrows)),
  IconButton(iconSize: 75, onPressed:(){ ble.send(RIGHT);},
    icon: Icon(Icons.arrow_forward_rounded)),    
]),

// 5th row
IconButton(iconSize: 75, onPressed:(){ ble.send(BACK);},
icon: Icon(Icons.arrow_circle_down)),
    
//6th row
IconButton(iconSize: 50, onPressed:() async {
  ble.send(STOP);
  ble.send(CENTER);
  ble.disconnect();
  SystemNavigator.pop();},
  icon: Icon(Icons.power_settings_new))      
        
]));}}
      

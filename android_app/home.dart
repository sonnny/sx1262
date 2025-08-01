import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import './globals.dart';

class Home extends StatefulWidget{
  Home({super.key});
  @override State<Home> createState() => HomeState();}
  
class HomeState extends State<Home>{
  Key key = UniqueKey();
  late BluetoothDevice device;
  String? status = 'connect';
  bool isConnected = false;
  var tx;
  
  void send(List<int> data) async {
    try{await tx.write(data, withoutResponse: true);} catch(e){}}
      
  void connect() async {
    device = BluetoothDevice(
    remoteId: DeviceIdentifier(BLE_ADDRESS));
    await device.connect();//connect without bluetooth scan
    List<BluetoothService> services = await device.discoverServices();
    tx = BluetoothCharacteristic(remoteId: device.remoteId,
      serviceUuid: Guid(SERVICE),
      characteristicUuid: Guid(TX_CHAR));
    setState((){status = 'ready'; 
      isConnected = true;});}
      
@override Widget build(BuildContext context){
return Scaffold(appBar: AppBar(title: Text('Ble boat rc')),
body: Column(spacing: 30, children:[

//1st row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround, 
  children: [     
    Text('address: ${BLE_ADDRESS}'),
    ElevatedButton(child:Text('${status}',
      style: isConnected ? connectedStyle : 
      notConnectedStyle), onPressed:() => connect())]),

//2nd row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
children: [
  ElevatedButton(child: Text('<<<<',style: forwardStyle), onPressed:(){send(FW4);}),
  ElevatedButton(child: Text('<<<',style: forwardStyle), onPressed:(){ send(FW3);}),
  ElevatedButton(child: Text('<<',style: forwardStyle), onPressed:(){  send(FW2);}),
  ElevatedButton(child: Text('<', style: forwardStyle), onPressed:(){   send(FW1);})]),
  
//3rd row
IconButton(iconSize: 75, onPressed:(){send(STOP);},
  icon: Icon(Icons.hexagon,
  color: Colors.red)),
  
//4th row
Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
children: [
  IconButton(iconSize: 75, onPressed:(){send(LEFT);},
    icon: Icon(Icons.arrow_back_rounded)),
  IconButton(iconSize: 75, onPressed:(){send(BACK);},
    icon: Icon(Icons.arrow_circle_down)),
  IconButton(iconSize: 75, onPressed:(){send(RIGHT);},
    icon: Icon(Icons.arrow_forward_rounded)),    
]),

//5th row
Padding(padding:EdgeInsets.all(20),
child:ElevatedButton(child:Text('exit'),
onPressed:() async {await device.disconnect();
SystemNavigator.pop();}))
           
]));}}
    

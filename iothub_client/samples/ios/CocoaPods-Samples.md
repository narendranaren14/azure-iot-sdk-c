# Building iOS samples for Azure IoT with CocoaPods

#### Prerequisites
 You will need these prerequisites to run the samples:
* The latest version of XCode
* The latest version of the iOS SDK
* [The latest version of CocoaPods](https://guides.cocoapods.org/using/index.html) and 
familiarity with their basic usage. Some more detail about the Azure IoT CocoaPods
may be found [here](https://github.com/Azure/azure-iot-sdk-c/tree/master/iothub_client/samples/ios/CocoaPods.md).
* An IoT Hub and a connection string for a client device.

#### 1. Clone the Azure IoT C SDK repo

Change to a location where you would like your samples, and run

`git clone https://github.com/Azure/azure-iot-sdk-c.git`

It is not necessary to do a recursive clone to build the iOS samples.

#### 2. Navigate to the sample directory

Change your current directory to the sample that you'd like to run. For 
example, the sample for AMQP would be:

`cd azure-iot-sdk-c/iothub_client/samples/ios/AMQP-Client-Sample`

**Note:** The samples do not need to be within the SDK tree, so you may copy them to a 
convenient location instead of building them within the tree.

#### 3. Install the CocoaPods

Make sure that XCode does not already have the sample project open. If
it does, the CocoaPods may not install properly.

Run this command:

`pod install`

This will cause CocoaPods to read the `Podfile` and install the pods accordingly.

One output of the `pod install` command will be an XCode workspace named 
`<sample name>_WS`. 

#### 4. Set your connection string

Open the `ViewController.swift` file and replace the `<insert connections string here>` string with
the connection string for your provisioned device.

#### 5. Run the app in the simulator

Open the `<sample name>_WS` workspace file that `pod install` generated, select your
desired target device (iPhone 7 works well), then build and run the project.

Make sure you open the workspace, and not the similarly-named (without the `_WS`) project.

Once the project is running in the simulator, click the "Start" hyperlink to begin
sending and receiving messages.



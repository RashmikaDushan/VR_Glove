using System.Collections;
using UnityEngine;
using System.IO.Ports;
using TMPro;
using System;
using UnityEngine.XR;
public class SerialConnection : MonoBehaviour
{
    SerialPort serialPort = new SerialPort("COM3", 460800); // Serial port for reading data
    private string receivedString; // Data received from the serial port
    private string sendString; // Data to be sent to the serial port
    private string[] stringData; // Received data as strings
    private float[] floatData = new float[14] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Recieved data as floats yaw,pitch,roll,index,middle,ring,pinky
    private float[] rotationOffset = new float[3] { 0, 0, 0};
    private float[] rotationOffset1 = new float[3] { 0, 0, 0};
    private float[] rotationOffset2 = new float[3] { 0, 0, 0};
    public TextMeshProUGUI onScreenText; // Text to display necessary data
    public GameObject[] fingerFirstJoints = new GameObject[5]; // Array of first joints of the fingers
    public GameObject[] fingerSecondJoints = new GameObject[5]; // Array of second joints of the fingers
    public GameObject[] fingerThirdJoints = new GameObject[5]; // Array of third joints of the fingers
    private int[] fingerCollided = new int[5] { 0, 0, 0, 0, 0 }; // Array to check if the fingers are collided
    public int[] fingerCollidedDebug = new int[5] { 0, 0, 0, 0, 0 }; // Array to check if the fingers are collided
    public float index; // variables for debuging
    public float middle;
    public float ring;
    public float pinky;
    public float thumb;

    public GameObject palm; // The palm object
    public GameObject forearm; // The forearm object
    public GameObject arm; // The arm object
    private float conversionFactor = 180.0f; // Conversion factor to convert the data to degrees
    bool debug=false;

    void Start()
    {
        serialPort.Open(); // Initiate the Serial stream
        SerialCommunication();
        ResetTransform();
    }

    void Update()
    {
        SerialCommunication();
        palm.transform.localEulerAngles = new Vector3(-floatData[1]-rotationOffset[0], floatData[0]-rotationOffset[1], -floatData[2]-rotationOffset[2]);
        forearm.transform.localEulerAngles = new Vector3(-floatData[4]-rotationOffset1[0], floatData[3]-rotationOffset1[1], -floatData[5]-rotationOffset1[2]);
        arm.transform.localEulerAngles = new Vector3(-floatData[7]-rotationOffset2[0], floatData[6]-rotationOffset2[1], -floatData[8]-rotationOffset2[2]);
        // this.transform.localRotation = Quaternion.Euler(intData[0], intData[1], intData[2]);
        FingerBend(0, floatData[12]);
        FingerBend(1, floatData[11]);
        FingerBend(2, floatData[10]);
        FingerBend(3, floatData[9]);
        // FingerBend(4, floatData[13]);
        // FingerBend();
        // string arrayValues = string.Join(", ", fingerCollided);
        // Debug.Log("boolArray: " + arrayValues);
        // SendData();
    }

    void OnApplicationQuit()
    {
        serialPort.Close(); // Close the Serial stream
    }
    void FingerBend(int fingerNumber, float bentPercentage)
    {
        if (bentPercentage < 4096 || bentPercentage >= 0)
        {
            if (fingerNumber == 4)
            {
                fingerFirstJoints[fingerNumber].transform.localRotation = Quaternion.Euler((bentPercentage * conversionFactor), 0, 0);
                fingerSecondJoints[fingerNumber].transform.localRotation = Quaternion.Euler((bentPercentage * conversionFactor), 0, 0);
                fingerThirdJoints[fingerNumber].transform.localRotation = Quaternion.Euler((bentPercentage * conversionFactor), 0, 0);
            }
            else if (fingerNumber <= 3 || fingerNumber >= 0)
            {
                fingerFirstJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (bentPercentage * conversionFactor));
                fingerSecondJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (bentPercentage * conversionFactor));
                fingerThirdJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (bentPercentage * conversionFactor));
            }
            else
            {
                Debug.LogWarning("Invalid finger number");
            }
        }
        else
        {
            Debug.LogWarning("Invalid bent percentage");
        }
    }
    public void RecordCollision(int fingerNumber)
    {
        fingerCollided[fingerNumber] = 1;
    }
    public void ClearCollision(int fingerNumber)
    {
        fingerCollided[fingerNumber] = 0;
    }
    public void ResetTransform()
    {
        rotationOffset[0] = -floatData[2];
        rotationOffset[1] = floatData[0];
        rotationOffset[2] = floatData[1];

        rotationOffset1[0] = -floatData[5];
        rotationOffset1[1] = floatData[3];
        rotationOffset1[2] = floatData[4];

        rotationOffset2[0] = -floatData[8];
        rotationOffset2[1] = floatData[6];
        rotationOffset2[2] = floatData[7];
    }
    private void SerialCommunication(){
        if(debug){
            sendString = string.Join(", ", fingerCollidedDebug); // prepare the data to be sent to the serial port
        }
        else{
            sendString = string.Join(", ", fingerCollided); // prepare the data to be sent to the serial port
        }
        
        if (serialPort.IsOpen && serialPort.BytesToRead > 0)
        {
            try
            {
                receivedString = serialPort.ReadLine(); // Read the data from the serial port
                stringData = receivedString.Split(',');
                floatData = Array.ConvertAll(stringData, float.Parse);
                serialPort.WriteLine(sendString); // Send the data to the serial port
                Debug.Log("Converted floatData: " + string.Join(", ", floatData)); // Debug log the converted floatData
                if(debug){
                    Debug.Log("FingerCollided Debug: " + sendString);
                }
                else{
                    Debug.Log("FingerCollided: " + sendString);
                }
                onScreenText.text = "FingerCollided: " + sendString;
                // Debug.Log("Received: " + receivedString);
            }
            catch (System.Exception e)
            {
                Debug.LogWarning("Error reading from serial port: " + e.Message);
                // onScreenText.text = "Error reading from serial port.";
            }
        }
    }

    //     public void resetTransform()
    // {
    //     rotationOffset[0] = -floatData[2];
    //     rotationOffset[1] = floatData[0];
    //     rotationOffset[2] = floatData[1];
    //     Debug.Log("Rotation Euler: " + string.Join(", ", rotationOffset)); // Debug log the converted floatData
    // }

    // void SendData()
    // {
    //     if (serialPort != null && serialPort.IsOpen)
    //     {
    //         string data = $"{fingerCollided[0]},{fingerCollided[1]},{fingerCollided[2]},{fingerCollided[3]},{fingerCollided[4]}\n";
    //         serialPort.WriteLine(data); // Send the data string
    //         Debug.Log($"Sent: {data}");
    //     }
    // }
}


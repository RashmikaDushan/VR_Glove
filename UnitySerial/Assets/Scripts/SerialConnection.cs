using System.Collections;
using UnityEngine;
using System.IO.Ports;
using TMPro;
using System;
using UnityEngine.XR;
public class SerialConnection : MonoBehaviour
{
    SerialPort serialPort = new SerialPort("COM3", 115200); // Serial port for reading data
    private string receivedString; // Data received from the serial port
    private string sendString; // Data to be sent to the serial port
    private string[] stringData; // Received data as strings
    private float[] floatData = new float[7] { 0, 0, 0, 0, 0, 0, 0}; // Recieved data as floats yaw,pitch,roll,index,middle,ring,pinky
    private float[] rotationOffset = new float[3] { 0, 0, 0};
    public TextMeshProUGUI onScreenText; // Text to display necessary data
    public GameObject[] fingerFirstJoints = new GameObject[5]; // Array of first joints of the fingers
    public GameObject[] fingerSecondJoints = new GameObject[5]; // Array of second joints of the fingers
    public GameObject[] fingerThirdJoints = new GameObject[5]; // Array of third joints of the fingers
    private bool[] fingerCollided = new bool[5] { false, false, false, false, false }; // Array to check if the fingers are collided
    public float index; // variables for debuging
    public float middle;
    public float ring;
    public float pinky;
    public float thumb;

    public GameObject hand; // The hand object
    private float conversionFactor = 180.0f; // Conversion factor to convert the data to degrees

    void Start()
    {
        serialPort.Open(); // Initiate the Serial stream
        SerialCommunication();
        ResetTransform();
    }

    void Update()
    {
        SerialCommunication();
        hand.transform.localEulerAngles = new Vector3(-floatData[1]-rotationOffset[0], floatData[0]-rotationOffset[1], -floatData[2]-rotationOffset[2]);
        // this.transform.localRotation = Quaternion.Euler(intData[0], intData[1], intData[2]);
        FingerBend(0, floatData[3]);
        FingerBend(1, floatData[4]);
        FingerBend(2, floatData[5]);
        FingerBend(3, floatData[6]);
        FingerBend(4, thumb);
        // FingerBend();
        // string arrayValues = string.Join(", ", fingerCollided);
        // Debug.Log("boolArray: " + arrayValues);
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
        fingerCollided[fingerNumber] = true;
    }
    public void ClearCollision(int fingerNumber)
    {
        fingerCollided[fingerNumber] = false;
    }
    public void ResetTransform()
    {
        rotationOffset[0] = -floatData[2];
        rotationOffset[1] = floatData[0];
        rotationOffset[2] = floatData[1];
    }
    private void SerialCommunication(){
        sendString = string.Join(", ", fingerCollided); // prepare the data to be sent to the serial port

        if (serialPort.IsOpen)
        {
            try
            {
                receivedString = serialPort.ReadLine(); // Read the data from the serial port
                stringData = receivedString.Split(',');
                floatData = Array.ConvertAll(stringData, float.Parse);
                serialPort.WriteLine(sendString); // Send the data to the serial port
                Debug.Log("Converted floatData: " + string.Join(", ", floatData)); // Debug log the converted floatData
            }
            catch (System.Exception e)
            {
                Debug.LogWarning("Error reading from serial port: " + e.Message);
                onScreenText.text = "Error reading from serial port.";
            }
        }
    }
}

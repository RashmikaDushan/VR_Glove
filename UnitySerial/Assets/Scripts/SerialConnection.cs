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
    private int[] intData = new int[5] { 0, 0, 0, 0, 0 }; // Recieved data as integers
    private float[] floatData = new float[3] { 0, 0, 0}; // Recieved data as floats
    private float[] rotationOffset = new float[3] { 0, 0, 0};
    public TextMeshProUGUI onScreenText; // Text to display necessary data
    public GameObject[] fingerFirstJoints = new GameObject[5]; // Array of first joints of the fingers
    public GameObject[] fingerSecondJoints = new GameObject[5]; // Array of second joints of the fingers
    public GameObject[] fingerThirdJoints = new GameObject[5]; // Array of third joints of the fingers
    private bool[] fingerCollided = new bool[5] { false, false, false, false, false }; // Array to check if the fingers are collided
    public int index; // variables for debuging
    public int middle;
    public int ring;
    public int pinky;
    public int thumb;

    public GameObject hand; // The hand object
    private float conversionFactor = 45.5111111f; // Conversion factor to convert the data to degrees

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
        FingerBendDebug(0, index);
        FingerBendDebug(1, middle);
        FingerBendDebug(2, ring);
        FingerBendDebug(3, pinky);
        FingerBendDebug(4, thumb);
        // FingerBend();
        // string arrayValues = string.Join(", ", fingerCollided);
        // Debug.Log("boolArray: " + arrayValues);
    }

    void OnApplicationQuit()
    {
        serialPort.Close(); // Close the Serial stream
    }
    void FingerBendDebug(int fingerNumber, int bentPercentage)
    {
        if (bentPercentage < 4096 || bentPercentage >= 0)
        {
            if (fingerNumber == 4)
            {
                fingerFirstJoints[fingerNumber].transform.localRotation = Quaternion.Euler((float)(bentPercentage / conversionFactor), 0, 0);
                fingerSecondJoints[fingerNumber].transform.localRotation = Quaternion.Euler((float)(bentPercentage / conversionFactor), 0, 0);
                fingerThirdJoints[fingerNumber].transform.localRotation = Quaternion.Euler((float)(bentPercentage / conversionFactor), 0, 0);
            }
            else if (fingerNumber <= 3 || fingerNumber >= 0)
            {
                fingerFirstJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (float)(bentPercentage / conversionFactor));
                fingerSecondJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (float)(bentPercentage / conversionFactor));
                fingerThirdJoints[fingerNumber].transform.localRotation = Quaternion.Euler(0, 0, (float)(bentPercentage / conversionFactor));
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
    void FingerBend()
    {
        for (int i = 0; i < 5; i++)
        {
            if (intData[i] < 4096 || intData[i] >= 0)
            {
                if (i == 4)
                {
                    fingerFirstJoints[i].transform.localRotation = Quaternion.Euler((float)(intData[i] / conversionFactor), 0, 0);
                    fingerSecondJoints[i].transform.localRotation = Quaternion.Euler((float)(intData[i] / conversionFactor), 0, 0);
                    fingerThirdJoints[i].transform.localRotation = Quaternion.Euler((float)(intData[i] / conversionFactor), 0, 0);
                }
                else if (i <= 3 || i >= 0)
                {
                    fingerFirstJoints[i].transform.localRotation = Quaternion.Euler(0, 0, (float)(intData[i] / conversionFactor));
                    fingerSecondJoints[i].transform.localRotation = Quaternion.Euler(0, 0, (float)(intData[i] / conversionFactor));
                    fingerThirdJoints[i].transform.localRotation = Quaternion.Euler(0, 0, (float)(intData[i] / conversionFactor));
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

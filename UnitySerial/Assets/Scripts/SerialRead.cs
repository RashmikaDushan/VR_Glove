using System.Collections;
using UnityEngine;
using System.IO.Ports;
using TMPro;
using System;
public class TestConnection : MonoBehaviour
{
    SerialPort data_stream = new SerialPort("COM3", 19200); // Serial port for reading data
    private string receivedString; // Data received from the serial port
    private string[] stringData; // Received data as strings
    private int[] intData; // Recieved data as integers
    public TextMeshProUGUI onScreenText;
    public GameObject indexFinger;
    public GameObject middleFinger;
    public GameObject ringFinger;
    public GameObject pinkyFinger;
    public GameObject thumbFinger;

    public float index;
    public float middle;
    public float ring;
    public float pinky;
    public float thumb;
    private float[] RotOffset = new float[5]{108.339f,0,0,0,0};

    void Start()
    {
        data_stream.Open(); // Initiate the Serial stream
    }

    void Update()
    {
        if (data_stream.IsOpen)
        {
            try
            {
                receivedString = data_stream.ReadLine();
                stringData = receivedString.Split(',');
                intData = Array.ConvertAll(stringData, int.Parse);
                onScreenText.SetText(((float)(intData[0] / 45.5111111)).ToString());
                indexFinger.transform.localRotation = Quaternion.Euler(0, 0, index + RotOffset[4]);
                middleFinger.transform.localRotation = Quaternion.Euler(0, 0, middle + RotOffset[4]);
                ringFinger.transform.localRotation = Quaternion.Euler(0, 0, ring + RotOffset[4]);
                pinkyFinger.transform.localRotation = Quaternion.Euler(0, 0, pinky + RotOffset[4]);
                thumbFinger.transform.localRotation = Quaternion.Euler(thumb + RotOffset[4],0,0);
            }
            catch (System.Exception e)
            {
                Debug.LogWarning("Error reading from serial port: " + e.Message);
            }
        }
    }
}

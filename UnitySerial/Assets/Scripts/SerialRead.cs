using System.Collections;
using UnityEngine;
using System.IO.Ports;
using TMPro;
using System;
public class TestConnection : MonoBehaviour
{
    SerialPort data_stream = new SerialPort("COM3", 19200);
    private string receivedstring;
    private int[] intdata;
    private string[] datas;
    public TextMeshProUGUI text1;
    public GameObject indexFinger;

    public float i;
    private float indexRotOffset = 108.339f;

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
                receivedstring = data_stream.ReadLine(); 
                datas = receivedstring.Split(',');
                intdata = Array.ConvertAll(datas, int.Parse);
                text1.SetText(((float)(intdata[0]/45.5111111)).ToString());
                indexFinger.transform.eulerAngles = new Vector3(0,0,i+indexRotOffset);
            }
            catch (System.Exception e)
            {
                Debug.LogWarning("Error reading from serial port: " + e.Message);
            }
        }
    }
}

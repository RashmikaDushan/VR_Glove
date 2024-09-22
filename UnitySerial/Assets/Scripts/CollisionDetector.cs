using System.Collections;
using UnityEngine;
using UnityEngine.XR;

public class CollisionDetector : MonoBehaviour
{
    private SerialConnection serialConnection;
    public int fingerNumber;

    void Start()
    {
        serialConnection = FindAnyObjectByType<SerialConnection>();
    }
    void OnTriggerEnter(Collider col)
    {
        if(col.gameObject.tag != "hand")
        {
            Debug.Log("Collision detected");
            serialConnection.RecordCollision(fingerNumber);
        }
    }
    void OnTriggerExit(Collider col)
    {
        if(col.gameObject.tag != "hand")
        {
            Debug.Log("Collision detected");
            serialConnection.ClearCollision(fingerNumber);
        }
    }
}
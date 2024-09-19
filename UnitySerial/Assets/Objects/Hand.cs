using System.Collections;
using UnityEngine;
using UnityEngine.XR;

public class DestroyCubes : MonoBehaviour
{
    float i;
    public GameObject Hand;
    // Start is called before the first frame update
    void OnCollisionEnter(Collision col)
    {
        if(col.gameObject.tag != "hand")
        {
            Destroy(col.gameObject);
        }
        
    }
    void Start()
    {
        i = 0;
    }

    // Update is called once per frame
    void Update()
    {
        i += (float)0.01;
        Hand.transform.position = new Vector3(0,i,0);

    }
}

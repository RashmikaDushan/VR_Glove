using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collision : MonoBehaviour
{
    // Start is called before the first frame update
    void OnCollisionEnter(Collision col)
    {
        if(col.gameObject.name != "hand")
        {
            Destroy(col.gameObject);
        }
        
    }
}

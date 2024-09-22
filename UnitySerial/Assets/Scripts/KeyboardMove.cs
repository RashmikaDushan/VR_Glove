using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class KeyboardMove : MonoBehaviour
{
    private Rigidbody hand;
    private float movementX;
    private float movementY;
    void Start()
    {
        hand = GetComponent<Rigidbody>();
    }

    void OnMove(InputValue value)
    {
        Vector2 force = value.Get<Vector2>();
        movementX = force.x;
        movementY = force.y;
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 movement = new Vector3(movementX, movementY, 0.0f);
        // hand.AddForce(movement);
        hand.velocity = movement;
    }
}

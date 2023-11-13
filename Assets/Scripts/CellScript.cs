using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CellScript : MonoBehaviour
{
    public float moveSpeed = 0;
    private Vector3 farPositiveCorner;
    private float cellRadius = 0;

    // Start is called before the first frame update
    void Start()
    {
        // Get the radius of this Cell object from its collider (to prevent overlapping the screen edges)
        cellRadius = GetComponent<CircleCollider2D>().radius;

        // Calculate the farthest positive point from the origin in world coordinates, leaving a buffer for the Cell's radius
        farPositiveCorner = Camera.main.ScreenToWorldPoint(new Vector2(Screen.width, Screen.height));
        farPositiveCorner.x = Math.Abs(farPositiveCorner.x) - cellRadius;
        farPositiveCorner.y = Math.Abs(farPositiveCorner.y) - cellRadius;

        // Get a random movement speed for this Cell
        moveSpeed = UnityEngine.Random.Range(0, Screen.width / 5);
    }

    // Update is called once per frame
    void Update()
    {
        // Get a random normalized vector in 3D space
        Vector3 moveVector = UnityEngine.Random.onUnitSphere;
        // Set the normalized vector's z component to zero for 2D
        moveVector.z = 0;
        // Scale the normalized vector by the Cell's move speed and the time elapsed since the last frame
        moveVector *= moveSpeed * Time.deltaTime;

        // Calculate the next position of the Cell
        Vector3 nextPosition = transform.position + moveVector;

        // If the next position overlaps the edge buffer, invert the movement in that direction
        if (Math.Abs(nextPosition.x) > farPositiveCorner.x)
        {
            moveVector.x *= -1;
        }

        if (Math.Abs(nextPosition.y) > farPositiveCorner.y)
        {
            moveVector.y *= -1;
        }

        // Apply the transformation
        transform.position += moveVector;
    }
}

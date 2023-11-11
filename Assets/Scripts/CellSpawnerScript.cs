using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CellSpawnerScript : MonoBehaviour
{
    public GameObject cell; // A cell prefab
    public ushort spawnAmount = 0;  // The number of cells to create when the game starts

    // Start is called before the first frame update
    void Start()
    {
        // Calculate the extents of the screen (seen through the main camera) in world coordinates
        Vector3 cameraOrigin = Camera.main.ScreenToWorldPoint(new Vector2(0, 0));
        Vector3 cameraFarCorner = Camera.main.ScreenToWorldPoint(new Vector2(Screen.width, Screen.height));

        // Get the radius of a cell object from its collider (to prevent overlapping the screen edges)
        float cellRadius = cell.GetComponent<CircleCollider2D>().radius;

        // Spawn up to spawnAmount cells at random locations in the screen
        for (int i = 0; i < spawnAmount; i++)
        {
            // Get random x and y values (in world coordinates), keeping a buffer of cellRadius around the screen edge
            float randX = Random.Range(cameraOrigin.x + cellRadius, cameraFarCorner.x - cellRadius);
            float randY = Random.Range(cameraOrigin.y + cellRadius, cameraFarCorner.y - cellRadius);
            // Make a position vector of the random x- and y-values
            Vector2 spawnPosition = new Vector2(randX, randY);

            // Create a cell object at the random position
            Instantiate(cell, spawnPosition, Quaternion.identity);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}

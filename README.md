# Wave-Progression-Unreal-Script

## Importing into UE4.
To import this into UE4 please follow the following steps:
Copy both of the downloaded cpp and .h files into:
DestinationProject\Source\DestinationProject

Open up the header file and replace:


![Image](https://i.gyazo.com/ff752ac9b1686193e680f48753008858.png)

CPPSCRIPTING_API to (Your project name)_API.

In Visual Studio, right click your destination project and then choose Add -> Existing Item, and choose the CPP and header file.

If you are still stuck, please follow the guide here: https://answers.unrealengine.com/questions/206693/how-can-i-export-class-file-to-another-project.html

## Using the script
Attach this script to an Actor component. This actor can be placed anywhere in the scene. Ensure that it does not have any rendering.
In the inspector, add in at least one enemy into slot 1, 2, 3, 4 or 5.
Then, add a spawner Actor to your scene, and place it wherever you want enemies to spawn from. Add this spawner into the spawner array in the inspector.
Finally, configure all of your arrays where appropriate!

When an enemy is killed, you need to call "EnemyKilled" from the relevant actor, for every enemy that has been killed. Otherwise, the script will not progress correctly.
Once all enemies have been killed, the next wave will immediately start.

Note: You will need to program the method "AllWavesCompleted" yourself. There is no code implemented in this method, as it is up to you.

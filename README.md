# Minigin_Engine

## Goal
Create a 2D component based engine and remake "QBert" with it. (assignment for second year Digital Arts and Entertainment programming course)

## Quick engine overview

## RENDERING
Rendering is done via openGL for smooth rasterization. This gives the user more control on what he/she wants to draw.

ImGui is available in the engine for quick and easy HUD drawing. You'll see it be used for QBert.
Text and Image rendering is also available via their respective components.

## COMPONENTS
Engine makes use of an entity component system.
All gameobjects are made of different components.

GameObjects are the component holders and can hold an infinite amount of components. The user can fetch, add and delete components from this gameobject.

## COLLISION
A seperate collision pass gets done at the end of the game, no grid optimization was done due to the simplicity of the desired game. All entities collide via small colliders under their feet.

The collision components are stored seperately from the other components.
This way the collision pass doesn't have to go through all the components and cast it to a collision component.
The colliders make use of the observer pattern and notify subscribed collision observers of a collision event. These observers are in charge of letting their components know that a collision happened.

## MENU
The menu components (or any components) can get notified of a mouse click via a mouse observer

## SOUND
The sound system processes the sound queue on a seperate thread. The engine allows for easy sound system swapping in case logging needs to happen / a different sound system is required.

## SINGLETONS
I chose to keep the deltatime in a seperate singleton. This way I only get the deltatime when I actually need it.

## SCENES
The scene manager allows for easy scene swapping, only the active scene gets rendered and updated.
All scenes initialize on game start.

## COMMANDS
Commands can be used to open scenes and various other things. You can attach commands to inputs so that they will automatically execute when the input is triggered.

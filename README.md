# Music Fingering Position Generator

A personal project with the goal of creating software to automically construct a 
fingering position sequence for a given	music score (for a single bowed string 
instrument). By using user defined preferences and instrument definitions the 
software should be able to give a good base of fingering positions when fed a sheet 
music MusicXML file. Uses the mx library (found at https://github.com/webern/mx) for 
MusicXML parsing.

## ------------- TODOS ---------------

-- Rebuild GreedySolver
-- Add a real shortest path solver (Dijsktras)
-- Create acceptance tests for greedysolver
-- Add doc explaining the abstract idea and implementation
-- Add more cases for github actions

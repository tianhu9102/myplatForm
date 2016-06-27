#ifndef TEXTACTOR_H
#define TEXTACTOR_H

#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkRenderer.h>

class TextActor
{
public:
    TextActor();

    void displayTextActors(vtkRenderer *renderer, int FontSize);

private:
    vtkTextActor* textActorT;
    vtkTextActor* textActorN;
    vtkTextActor* textActorB;
};

#endif // TEXTACTOR_H

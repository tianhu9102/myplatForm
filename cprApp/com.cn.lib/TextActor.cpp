#include "TextActor.h"

//!--------------------------------------------------------------------------------
//!
//! \brief TextActor::TextActor
//!
//!  this class is used to display a 3 vtkTextActors
//!
//!  test successfully!
//!  date: 2016-05-10    add: ShenZhen
//!--------------------------------------------------------------------------------

TextActor::TextActor()
{
    textActorT = vtkTextActor::New();
    textActorN = vtkTextActor::New();
    textActorB = vtkTextActor::New();
}

//!--------------------------------------------------------------------------------
//!
//! \brief TextActor::displayTextActors
//! \param renderer
//! \param fontSize
//!
void TextActor::displayTextActors(vtkRenderer *renderer, int FontSize){

    textActorT->SetInput("Tangent  --------- ");
    textActorT->GetTextProperty()->SetColor( 1.0, 0.0, 0.0 );
    textActorT->GetTextProperty()->SetFontSize(FontSize);   //14

    textActorN->SetInput("Normal    --------- ");
    textActorN->GetTextProperty()->SetColor( 0.0, 1.0, 0.0 );
    textActorN->GetTextProperty()->SetFontSize(FontSize);

    textActorB->SetInput("Binormal  --------- ");
    textActorB->GetTextProperty()->SetColor( 0.0, 0.0, 1.0 );
    textActorB->GetTextProperty()->SetFontSize(FontSize);

    renderer->AddActor2D(textActorT);
    renderer->AddActor2D(textActorN);
    renderer->AddActor2D(textActorB);

    textActorT->SetDisplayPosition(renderer->GetCenter()[0]*1.4, renderer->GetCenter()[1]*1.8);
    textActorB->SetDisplayPosition(renderer->GetCenter()[0]*1.4, renderer->GetCenter()[1]*1.6);
    textActorN->SetDisplayPosition(renderer->GetCenter()[0]*1.4, renderer->GetCenter()[1]*1.7);
}

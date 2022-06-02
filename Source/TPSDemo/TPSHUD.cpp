// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHUD.h"

void ATPSHUD::DrawHUD()
{
	Super::DrawHUD();
	if (CursorTexture)
	{
		FVector2D mousePos;
		GetWorld()->GetGameViewport()->GetMousePosition(mousePos);
		
		FVector2D hudPos(mousePos.X - CursorTexture->GetSurfaceWidth() * 0.5f, 
			             mousePos.Y - CursorTexture->GetSurfaceHeight() * 0.5f);
		FCanvasTileItem TileItem(hudPos, CursorTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}

}

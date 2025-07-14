// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMMagicCharacter.h"




APPMMagicCharacter::APPMMagicCharacter()
{

}

void APPMMagicCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APPMMagicCharacter::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void APPMMagicCharacter::UseAbility(int32 Abilities)
{

}

void APPMMagicCharacter::UpdateAnimation(EPPMCharacterState Action)
{
	UPaperFlipbookComponent* CurrentSprite = this->GetSprite();
	if (CurrentSprite)
	{
		UPaperFlipbook* CurrentFlipbook = CurrentSprite->GetFlipbook();
		UPaperFlipbook** NewFlipbook = FlipbookMap.Find(Action);
		if (CurrentFlipbook && NewFlipbook)
		{
			if (CurrentFlipbook != *NewFlipbook)
			{
				CurrentSprite->SetFlipbook(*NewFlipbook);
			}
		}
	}
}

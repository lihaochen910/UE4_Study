#pragma once

#define Log(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT(x)); }

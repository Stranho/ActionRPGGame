#pragma once
#include "GameTrace.h"
#include "GTTraceBase.h"
#include "GTTrace_GroundSphere.generated.h"
/*
	Base class for trace actions.
*/
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInLineNew)
class GAMETRACE_API UGTTrace_GroundSphere : public UGTTraceBase
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Configuration")
		TSubclassOf<class AGTTraceDisplayHelper> DisplayHelperActor;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		float Radius;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		TArray<TEnumAsByte<ECollisionChannel> > SphereObjectToTrace;

	/**/
	virtual void Tick(float DeltaSecondsIn) override;

	virtual void Initialize() override;

	/**
	*	Call it to display cosmetic helpers.
	*/
	virtual void PreExecute() override;

	/**
	 *	Central function to execute current action.
	 */
	virtual void Execute() override;

	virtual void PostExecute() override;

protected:
	UPROPERTY()
	class AGTTraceDisplayHelper* DisplayHelper;

	FCollisionObjectQueryParams SphereObjectParams;

	void SphereTrace();

};

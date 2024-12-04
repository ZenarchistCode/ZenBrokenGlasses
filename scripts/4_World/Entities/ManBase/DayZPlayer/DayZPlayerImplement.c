#ifndef SERVER // client-side only
modded class DayZPlayerImplement
{
	//! BROKEN GLASSES - TODO: Find a better way to hijack optics. Surely there's a way to slide into the PPE Effects's DMs?
	static ref array<string> DAMAGED_SCOPES =
	{
		"HuntingOptic",
		"Binoculars",
		"KazuarOptic",
		"LongRangeOptic",
		"Expansion_PMII25Optic",
		"AD_LeupoldMk4",
		"AD_Pilad",
		"AD_DHF5",
		"AD_NFATACR",
		"AD_NFATACR_1_8",
		"AD_PVS4"
	};

	override void SetOptics(bool value)
	{
		super.SetOptics(value);

		if (!value)
		{
			ZenBrokenGlassesWidget.GetZenBrokenGlassesWidget().HideFX_Optics();
		}
	}

	override void HandleOptic(notnull ItemOptics optic, bool inHands, HumanInputController pInputs, out bool pExitOptics)
	{
		super.HandleOptic(optic, inHands, pInputs, pExitOptics);

		if (!IsInOptics())
			return;

		// Only show on relevant optics that don't already have vanilla damage effects
		bool damagedScope = false;
		foreach(string s : DAMAGED_SCOPES)
		{
			if (optic.GetType().Contains(s) || optic.IsKindOf(s))
			{
				damagedScope = true;
				break;
			}
		}

		if (!damagedScope)
			return;

		ZenBrokenGlassesWidget.GetZenBrokenGlassesWidget().ShowFX_Optics(optic.GetHealthLevel());
	}
}
#endif
#undef TARGET_API_MAC_CARBON#define TARGET_API_MAC_OS8 1#import <Dialogs.h>OSErr __init (const CFragInitBlock *);OSErr __init (const CFragInitBlock *){	EventRecord event;	MaxApplZone ( );	InitGraf (&(qd.thePort));	SetCursor (*GetCursor (watchCursor));	InitFonts ( );	InitWindows ( );	InitMenus ( );	TEInit ( );	InitDialogs (nil);	WaitNextEvent (0,&event,0xFFFFFFFF,nil);	return noErr;}pascal Boolean QDIsPortBuffered (CGrafPtr) { return false; }#import "AuntieDialog.h"enum { kControlIDProperty = 'idid' };pascal OSStatus SetControlID (ControlRef inControl, const ControlID *inID){	OSStatus err = noErr;	if (!SetControlProperty) // in case we're on an old system	{		err = unimpErr;	}	else	{		err = SetControlProperty (inControl, 0, kControlIDProperty, sizeof (*inID), (void *) inID);	}	return err;}pascal OSStatus GetControlID (ControlRef inControl, ControlID *outID){	OSStatus err = noErr;	if (!GetControlProperty) // in case we're on an old system	{		err = unimpErr;	}	else	{		UInt32 actualSize, bufferSize = sizeof (*outID);		err = GetControlProperty (inControl,0,kControlIDProperty,bufferSize,&actualSize,outID);		if (!err && actualSize != bufferSize)		{			err = controlPropertyInvalid;		}	}	return err;}static pascal OSStatus ControlHasID (ControlRef candidate, Boolean *hasID, void *inTestID){	ControlID actualID;	OSStatus err = GetControlID (candidate, &actualID);	if (!err)	{		const ControlID *testID = (const ControlID *) inTestID;		*hasID = (actualID.signature == testID->signature && actualID.id == testID->id);	}	return err;}pascal OSStatus GetControlByID (WindowRef inWindow, const ControlID *inID, ControlRef *outControl){	return SearchControlHierarchy (inWindow, ControlHasID, outControl, (void*) inID);}
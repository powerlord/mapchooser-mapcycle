/**
 * vim: set ts=4 :
 * =============================================================================
 * Read MapCycle
 * Functions to read the ServerMapCycle from server memory
 * Based on an idea by nosoop
 *
 * Read MapCycle (C)2016 Powerlord (Ross Bemrose).  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */
#if defined _readmapcycle_included_
  #endinput
#endif
#define _readmapcycle_included_
#include <sdktools>

/**
 * Read the server's mapcycle from the mapcycle table.
 *
 * @param mapList		The current mapList to update or null. If you pass in null,
 * 						a new ArrayList will be created.
 * @param clearArray	If true, clear the array before populating it with new values.
 *
 * @return				The updated mapList.  It will be the same Handle as mapList unless
 *						you passed in null.
 */
stock ArrayList ReadMapCycleTable(ArrayList mapList, bool clearArray=true)
{
	ArrayList outList;
	int mapCycleTable = FindStringTable("ServerMapCycle");
	if (mapCycleTable == INVALID_STRING_TABLE)
	{
		delete mapList;
		return null;
	}
	
	int mapCycleEntry = FindStringIndex(mapCycleTable, "ServerMapCycle");
	
	int mapCycleLength = GetStringTableDataLength(mapCycleTable, mapCycleEntry);
	
	char[] data = new char[mapCycleLength];
	GetStringTableData(mapCycleTable, mapCycleEntry, data, mapCycleLength);
	
	char map[PLATFORM_MAX_PATH];
	
	if (mapList == null)
	{
		outList = new ArrayList(ByteCountToCells(PLATFORM_MAX_PATH));
	}
	else
	{
		outList = mapList;
	}
	
	if (clearArray)
	{
		outList.Clear();
	}
	
	int index = 0;
	int oldIndex = 0;
	
	while ((index = SplitString(data[oldIndex], "\n", map, sizeof(map))) != -1)
	{
		oldIndex += index;
		outList.PushString(map);
	}
	
	return outList;
}

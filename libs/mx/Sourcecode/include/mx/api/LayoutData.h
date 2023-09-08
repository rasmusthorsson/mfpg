// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/api/ApiCommon.h"
#include "mx/api/MeasureData.h"
#include "mx/api/PageData.h"
#include "mx/api/SystemData.h"

#include <map>

namespace mx
{
    namespace api
    {
        /// LayoutData represents the page and system layout instructions that
        /// are found in the <print> element. These are held in `ScoreData` in a
        /// map where the key is the measure index. For example, to start a new
        /// page at measure index 39:
        /// `score.layout.emplace( 39, LayoutData{ true, true } );`, where the
        /// constructor `LayoutData{ true, true }` is a constructor indicating
        /// that both a new system and a new page are indicated.
        class LayoutData
        {
        public:
            /// System information, such as whether a system break should occur.
            /// Note: all members are optional.
            SystemData system;

            /// Page information, such as whether a page break should occur.
            /// Note: all members are optional.
            PageData page;

            /// Convenience constructor for the use case where we only care
            /// about specifying system breaks and page breaks. That is, if you
            /// do not need to fuss with margins or spacing and only want to
            /// indicate the start of a new system or page, you can use this
            /// constructor. The first bool indicates that a new system should
            /// start. The second bool indicates that a new page should also
            /// start. For example: `LayoutData{ true }` produces 
            /// `<print new-system="yes" />` and `LayoutData{ true, true }`
            /// produces `<print new-system="yes" new-page="yes" />`
            inline explicit LayoutData( bool inNewSystem, bool inNewPage = false )
                : system{ inNewSystem ? Bool::yes : Bool::unspecified }
                , page{ inNewPage ? Bool::yes : Bool::unspecified }
            {

            }

            /// The default constructor does not specify any page or system
            /// details. i.e. a default constructed object will not produce a
            /// `<print>` element.
            inline LayoutData()
                : LayoutData{ SystemData{}, PageData{} }
            {

            }

            /// The explicit constructor takes fully constructed members.
            inline explicit LayoutData( SystemData inSystem, PageData inPage )
                : system{ std::move( inSystem ) }
                , page{ std::move( inPage ) }
            {

            }

            /// Tells us whether any members have been specified or not.
            inline bool isUsed() const { return system.isUsed() || page.isUsed(); }
        };

        MXAPI_EQUALS_BEGIN( LayoutData )
            MXAPI_EQUALS_MEMBER( system )
            MXAPI_EQUALS_MEMBER( page )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( LayoutData );

        inline bool operator==(
            const std::map<MeasureIndex, LayoutData>& a,
            const std::map<MeasureIndex, LayoutData>& b
        )
        {
            if( a.size() != b.size() )
            {
                return false;
            }
            auto ai = a.cbegin();
            auto bi = b.cbegin();
            const auto aend = a.cend();
            const auto bend = b.cend();
            for( ; ai != aend && bi != bend; ++ai, ++bi )
            {
                if( ai->first != bi->first )
                {
                    return false;
                }
                if( ai->second != bi->second )
                {
                    return false;
                }
            }
            return true;
        }
    }
}

// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/impl/DynamicsWriter.h"
#include "mx/core/elements/Dynamics.h"
#include "mx/impl/MarkDataFunctions.h"

namespace mx
{
    namespace impl
    {
        DynamicsWriter::DynamicsWriter( const api::MarkData& inMark, impl::Cursor inCursor )
        : myMarkData{ inMark }
        , myCursor{ inCursor }
        , myDirectionPlacement( api::Placement::unspecified )
        , myConverter{}
        {
            MX_ASSERT( isMarkDynamic(inMark.markType ) );
        }
        
        
        DynamicsWriter::DynamicsWriter( const api::MarkData& inMark, impl::Cursor inCursor, api::Placement directionPlacement )
        : myMarkData{ inMark }
        , myCursor{ inCursor }
        , myDirectionPlacement( directionPlacement )
        , myConverter{}
        {
            MX_ASSERT( isMarkDynamic(inMark.markType ) );
        }
        
        core::DynamicsPtr DynamicsWriter::getDynamics() const
        {
            auto dyn = core::makeDynamics();
            
            const auto value = myConverter.convertDynamic( myMarkData.markType );
            core::DynamicsValue dynamicsValue;
            dynamicsValue.setValue( value );
            const bool isOther = value == core::DynamicsEnum::otherDynamics;
            
            if ( isOther && !myMarkData.name.empty() )
            {
                dynamicsValue.setValue( myMarkData.name );
            }
            impl::setAttributesFromMarkData( myMarkData, *dyn->getAttributes() );
            dyn->setValue( dynamicsValue );
            return dyn;
        }
    }
}

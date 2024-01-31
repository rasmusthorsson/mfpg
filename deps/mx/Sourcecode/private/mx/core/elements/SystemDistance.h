// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Decimals.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( SystemDistance )

        inline SystemDistancePtr makeSystemDistance() { return std::make_shared<SystemDistance>(); }
		inline SystemDistancePtr makeSystemDistance( const TenthsValue& value ) { return std::make_shared<SystemDistance>( value ); }
		inline SystemDistancePtr makeSystemDistance( TenthsValue&& value ) { return std::make_shared<SystemDistance>( std::move( value ) ); }

        class SystemDistance : public ElementInterface
        {
        public:
            SystemDistance();
            SystemDistance( const TenthsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TenthsValue getValue() const;
            void setValue( const TenthsValue& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            TenthsValue myValue;
        };
    }
}

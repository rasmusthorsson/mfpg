// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Enums.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Mute )

        inline MutePtr makeMute() { return std::make_shared<Mute>(); }
		inline MutePtr makeMute( const MuteEnum& value ) { return std::make_shared<Mute>( value ); }
		inline MutePtr makeMute( MuteEnum&& value ) { return std::make_shared<Mute>( std::move( value ) ); }

        class Mute : public ElementInterface
        {
        public:
            Mute();
            Mute( const MuteEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MuteEnum getValue() const;
            void setValue( const MuteEnum& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            MuteEnum myValue;
        };
    }
}

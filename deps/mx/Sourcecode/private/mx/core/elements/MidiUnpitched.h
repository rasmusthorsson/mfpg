// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( MidiUnpitched )

        inline MidiUnpitchedPtr makeMidiUnpitched() { return std::make_shared<MidiUnpitched>(); }
		inline MidiUnpitchedPtr makeMidiUnpitched( const Midi128& value ) { return std::make_shared<MidiUnpitched>( value ); }
		inline MidiUnpitchedPtr makeMidiUnpitched( Midi128&& value ) { return std::make_shared<MidiUnpitched>( std::move( value ) ); }

        class MidiUnpitched : public ElementInterface
        {
        public:
            MidiUnpitched();
            MidiUnpitched( const Midi128& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            Midi128 getValue() const;
            void setValue( const Midi128& value );

            private:
            virtual bool fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement );

        private:
            Midi128 myValue;
        };
    }
}

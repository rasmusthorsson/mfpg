// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/impl/MeasureCursor.h"
#include "mx/impl/Converter.h"

namespace mx
{
    namespace core
    {
        class Notations;
        using NotationsPtr = std::shared_ptr<Notations>;
        class NotationsChoice;
        using NotationsChoicePtr = std::shared_ptr<NotationsChoice>;
        class Articulations;
        using ArticulationsPtr = std::shared_ptr<Articulations>;
        class Ornaments;
        using OrnamentsPtr = std::shared_ptr<Ornaments>;
        class Technical;
        using TechnicalPtr = std::shared_ptr<Technical>;
        
    }
    
    namespace impl
    {
        class ScoreWriter;
        
        class NotationsWriter
        {
        public:
            NotationsWriter( const api::NoteData& inNoteData, const MeasureCursor& inCursor, const ScoreWriter& inScoreWriter );
            core::NotationsPtr getNotations() const;
            
        private:
            const api::NoteData& myNoteData;
            const MeasureCursor& myCursor;
            const ScoreWriter& myScoreWriter;
            const Converter myConverter;
            mutable core::NotationsPtr myOutNotations;
            
        private:
            core::NotationsChoicePtr makeArticulationsNotationsChoice() const;
            core::NotationsChoicePtr makeOrnamentsNotationsChoice() const;
            core::NotationsChoicePtr makeTechnicalNotationsChoice() const;
            void addArticulation( const api::MarkData& markData, const core::ArticulationsPtr& outArticulationsPtr ) const;
            void addOrnament( const api::MarkData& markData, const core::OrnamentsPtr& outOrnamentsPtr ) const;
            void addTechnical( const api::MarkData& markData, const core::TechnicalPtr& outOrnamentsPtr ) const;
        };
    }
}

// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/impl/NotationsWriter.h"
#include "mx/core/elements/Accent.h"
#include "mx/core/elements/Arrow.h"
#include "mx/core/elements/Articulations.h"
#include "mx/core/elements/ArticulationsChoice.h"
#include "mx/core/elements/Bend.h"
#include "mx/core/elements/BreathMark.h"
#include "mx/core/elements/Caesura.h"
#include "mx/core/elements/DelayedInvertedTurn.h"
#include "mx/core/elements/DelayedTurn.h"
#include "mx/core/elements/DetachedLegato.h"
#include "mx/core/elements/Doit.h"
#include "mx/core/elements/DoubleTongue.h"
#include "mx/core/elements/DownBow.h"
#include "mx/core/elements/Dynamics.h"
#include "mx/core/elements/Falloff.h"
#include "mx/core/elements/Fermata.h"
#include "mx/core/elements/Fingering.h"
#include "mx/core/elements/Fingernails.h"
#include "mx/core/elements/Fret.h"
#include "mx/core/elements/HammerOn.h"
#include "mx/core/elements/Handbell.h"
#include "mx/core/elements/Harmonic.h"
#include "mx/core/elements/Heel.h"
#include "mx/core/elements/Hole.h"
#include "mx/core/elements/InvertedMordent.h"
#include "mx/core/elements/InvertedTurn.h"
#include "mx/core/elements/Mordent.h"
#include "mx/core/elements/Notations.h"
#include "mx/core/elements/NotationsChoice.h"
#include "mx/core/elements/OpenString.h"
#include "mx/core/elements/Ornaments.h"
#include "mx/core/elements/OrnamentsChoice.h"
#include "mx/core/elements/OtherArticulation.h"
#include "mx/core/elements/OtherOrnament.h"
#include "mx/core/elements/OtherTechnical.h"
#include "mx/core/elements/Plop.h"
#include "mx/core/elements/Pluck.h"
#include "mx/core/elements/PullOff.h"
#include "mx/core/elements/Schleifer.h"
#include "mx/core/elements/Scoop.h"
#include "mx/core/elements/Shake.h"
#include "mx/core/elements/Slur.h"
#include "mx/core/elements/SnapPizzicato.h"
#include "mx/core/elements/Spiccato.h"
#include "mx/core/elements/Staccatissimo.h"
#include "mx/core/elements/Staccato.h"
#include "mx/core/elements/Stopped.h"
#include "mx/core/elements/Stress.h"
#include "mx/core/elements/String.h"
#include "mx/core/elements/StrongAccent.h"
#include "mx/core/elements/Tap.h"
#include "mx/core/elements/Technical.h"
#include "mx/core/elements/Tenuto.h"
#include "mx/core/elements/ThumbPosition.h"
#include "mx/core/elements/Tied.h"
#include "mx/core/elements/Toe.h"
#include "mx/core/elements/Tremolo.h"
#include "mx/core/elements/TrillMark.h"
#include "mx/core/elements/TripleTongue.h"
#include "mx/core/elements/Tuplet.h"
#include "mx/core/elements/TupletActual.h"
#include "mx/core/elements/TupletDot.h"
#include "mx/core/elements/TupletNormal.h"
#include "mx/core/elements/TupletNumber.h"
#include "mx/core/elements/TupletType.h"
#include "mx/core/elements/Turn.h"
#include "mx/core/elements/Unstress.h"
#include "mx/core/elements/UpBow.h"
#include "mx/core/elements/VerticalTurn.h"
#include "mx/core/elements/WavyLine.h"
#include "mx/impl/CurveFunctions.h"
#include "mx/impl/DynamicsWriter.h"
#include "mx/impl/MarkDataFunctions.h"
#include "mx/utility/OptionalMembers.h"


namespace mx
{
    namespace impl
    {
        NotationsWriter::NotationsWriter( const api::NoteData& inNoteData, const MeasureCursor& inCursor, const ScoreWriter& inScoreWriter )
        : myNoteData{ inNoteData }
        , myCursor{ inCursor }
        , myScoreWriter{ inScoreWriter }
        , myConverter{}
        , myOutNotations{nullptr}
        {
            
        }
                
        core::NotationsPtr NotationsWriter::getNotations() const
        {
            myOutNotations = core::makeNotations();
            auto articulationsNotationChoice = makeArticulationsNotationsChoice();
            auto articulations = articulationsNotationChoice->getArticulations();
            auto ornamentsNotationChoice = makeOrnamentsNotationsChoice();
            auto ornaments = ornamentsNotationChoice->getOrnaments();
            auto technicalNotationChoice = makeTechnicalNotationsChoice();
            auto technicals = technicalNotationChoice->getTechnical();

            for( const auto& curve : myNoteData.noteAttachmentData.curveStops )
            {
                auto curveNotationsChoice = core::makeNotationsChoice();
                myOutNotations->addNotationsChoice( curveNotationsChoice );
                
                if( curve.curveType == api::CurveType::tie )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::tied );
                    auto element = curveNotationsChoice->getTied();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveStop( curve, *attr );
                }
                else if( curve.curveType == api::CurveType::slur )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::slur );
                    auto element = curveNotationsChoice->getSlur();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveStop( curve, *attr );
                }
            }

            for( const auto& curve : myNoteData.noteAttachmentData.curveContinuations )
            {
                auto curveNotationsChoice = core::makeNotationsChoice();
                myOutNotations->addNotationsChoice( curveNotationsChoice );
                
                if( curve.curveType == api::CurveType::tie )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::tied );
                    auto element = curveNotationsChoice->getTied();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveContinue( curve, *attr );
                }
                else if( curve.curveType == api::CurveType::slur )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::slur );
                    auto element = curveNotationsChoice->getSlur();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveContinue( curve, *attr );
                }
            }

            for( const auto& curve : myNoteData.noteAttachmentData.curveStarts )
            {
                auto curveNotationsChoice = core::makeNotationsChoice();
                myOutNotations->addNotationsChoice( curveNotationsChoice );
                
                if( curve.curveType == api::CurveType::tie )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::tied );
                    auto element = curveNotationsChoice->getTied();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveStart( curve, *attr );
                }
                else if( curve.curveType == api::CurveType::slur )
                {
                    curveNotationsChoice->setChoice( core::NotationsChoice::Choice::slur );
                    auto element = curveNotationsChoice->getSlur();
                    auto attr = element->getAttributes();
                    writeAttributesFromCurveStart( curve, *attr );
                }
            }
            
            
            
            for( const auto& tupletStop : myNoteData.noteAttachmentData.tupletStops )
            {
                auto tupletNotationsChoice = core::makeNotationsChoice();
                myOutNotations->addNotationsChoice( tupletNotationsChoice );
                tupletNotationsChoice->setChoice( core::NotationsChoice::Choice::tuplet );
                auto tuplet = tupletNotationsChoice->getTuplet();
                tuplet->getAttributes()->type = core::StartStop::stop;
                
                if( tupletStop.numberLevel > 0 )
                {
                    tuplet->getAttributes()->hasNumber = true;
                    tuplet->getAttributes()->number = core::NumberLevel{ tupletStop.numberLevel };
                }
            }
            
            for( const auto& tupletStart : myNoteData.noteAttachmentData.tupletStarts )
            {
                auto tupletNotationsChoice = core::makeNotationsChoice();
                myOutNotations->addNotationsChoice( tupletNotationsChoice );
                tupletNotationsChoice->setChoice( core::NotationsChoice::Choice::tuplet );
                auto tuplet = tupletNotationsChoice->getTuplet();
                tuplet->getAttributes()->type = core::StartStop::start;
                tuplet->setHasTupletActual( true );
                tuplet->setHasTupletNormal( true );

                tuplet->getTupletActual()->getTupletNumber()->setValue( core::NonNegativeInteger{ tupletStart.actualNumber } );
                tuplet->getTupletActual()->setHasTupletType( true );
                tuplet->getTupletActual()->getTupletType()->setValue( myConverter.convert( tupletStart.actualDurationName ) );
                for( int d = 0; d < tupletStart.actualDots; ++d )
                {
                    tuplet->getTupletActual()->addTupletDot( core::makeTupletDot() );
                }

                tuplet->getTupletNormal()->getTupletNumber()->setValue( core::NonNegativeInteger{ tupletStart.normalNumber } );
                tuplet->getTupletNormal()->setHasTupletType( true );
                tuplet->getTupletNormal()->getTupletType()->setValue( myConverter.convert( tupletStart.normalDurationName ) );
                for( int d = 0; d < tupletStart.normalDots; ++d )
                {
                    tuplet->getTupletNormal()->addTupletDot( core::makeTupletDot() );
                }

                tuplet->getTupletNormal()->setHasTupletNumber( true );
                tuplet->getTupletActual()->setHasTupletNumber( true );
                
                if( tupletStart.numberLevel > 0 )
                {
                    tuplet->getAttributes()->hasNumber = true;
                    tuplet->getAttributes()->number = core::NumberLevel{ tupletStart.numberLevel };
                }
                
                if( tupletStart.bracket != api::Bool::unspecified )
                {
                    tuplet->getAttributes()->hasBracket = true;
                    tuplet->getAttributes()->bracket = myConverter.convert( tupletStart.bracket );
                }
                
                if( tupletStart.showActualNumber != api::Bool::unspecified )
                {
                    auto& hasShow = tuplet->getAttributes()->hasShowNumber;
                    auto& show = tuplet->getAttributes()->showNumber;
                    
                    if( tupletStart.showActualNumber == api::Bool::yes )
                    {
                        if( tupletStart.showNormalNumber == api::Bool::yes )
                        {
                            hasShow = true;
                            show = core::ShowTuplet::both;
                        }
                        else
                        {
                            hasShow = true;
                            show = core::ShowTuplet::actual;
                        }
                    }
                    else if( tupletStart.showActualNumber == api::Bool::no )
                    {
                        hasShow = true;
                        show = core::ShowTuplet::none;
                    }
                }
            }
            
            
            
            for( const auto& mark : myNoteData.noteAttachmentData.marks )
            {
                if( isMarkArticulation( mark.markType ) || isMarkCustom( mark.markType ) )
                {
                    this->addArticulation( mark, articulations );
                }
                if( isMarkOrnament( mark.markType ) )
                {
                    this->addOrnament( mark, ornaments );
                }
                if( isMarkTechnical( mark.markType ) )
                {
                    this->addTechnical( mark, technicals );
                }
                else if( isMarkDynamic( mark.markType) )
                {
                    auto dynamicNotationsChoice = core::makeNotationsChoice();
                    myOutNotations->addNotationsChoice( dynamicNotationsChoice );
                    dynamicNotationsChoice->setChoice( core::NotationsChoice::Choice::dynamics );
                    DynamicsWriter dynamicsWriter{ mark, myCursor };
                    dynamicNotationsChoice->setDynamics( dynamicsWriter.getDynamics() );
                }
                else if( isMarkFermata( mark.markType ) )
                {
                    auto fermataNotationsChoice = core::makeNotationsChoice();
                    myOutNotations->addNotationsChoice( fermataNotationsChoice );
                    fermataNotationsChoice->setChoice( core::NotationsChoice::Choice::fermata );
                    auto& fermata = *fermataNotationsChoice->getFermata();
                    auto& attr = *fermata.getAttributes();
                    impl::setAttributesFromMarkData( mark, attr );
                    
                    if( mark.markType == api::MarkType::fermata )
                    {
                        fermata.setValue( core::FermataShape::emptystring );
                        attr.hasType = false;
                    }
                    else if( mark.markType == api::MarkType::fermataNormal )
                    {
                        fermata.setValue( core::FermataShape::normal );
                        attr.hasType = false;
                    }
                    else if( mark.markType == api::MarkType::fermataAngled )
                    {
                        fermata.setValue( core::FermataShape::angled );
                        attr.hasType = false;
                    }
                    else if( mark.markType == api::MarkType::fermataSquare )
                    {
                        fermata.setValue( core::FermataShape::square );
                        attr.hasType = false;
                    }
                    else if( mark.markType == api::MarkType::fermataUpright )
                    {
                        fermata.setValue( core::FermataShape::emptystring );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::upright;
                    }
                    else if( mark.markType == api::MarkType::fermataNormalUpright )
                    {
                        fermata.setValue( core::FermataShape::normal );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::upright;
                    }
                    else if( mark.markType == api::MarkType::fermataAngledUpright )
                    {
                        fermata.setValue( core::FermataShape::angled );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::upright;
                    }
                    else if( mark.markType == api::MarkType::fermataSquareUpright )
                    {
                        fermata.setValue( core::FermataShape::square );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::upright;
                    }
                    else if( mark.markType == api::MarkType::fermataInverted )
                    {
                        fermata.setValue( core::FermataShape::emptystring );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::inverted;
                    }
                    else if( mark.markType == api::MarkType::fermataNormalInverted )
                    {
                        fermata.setValue( core::FermataShape::normal );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::inverted;
                    }
                    else if( mark.markType == api::MarkType::fermataAngledInverted )
                    {
                        fermata.setValue( core::FermataShape::angled );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::inverted;
                    }
                    else if( mark.markType == api::MarkType::fermataSquareInverted )
                    {
                        fermata.setValue( core::FermataShape::square );
                        attr.hasType = true;
                        attr.type = core::UprightInverted::inverted;
                    }
                    
                }
            }
            
            if( articulations->getArticulationsChoiceSet().size() > 0 )
            {
                myOutNotations->addNotationsChoice( articulationsNotationChoice );
            }

            if( ornaments->getOrnamentsChoiceSet().size() > 0 )
            {
                myOutNotations->addNotationsChoice( ornamentsNotationChoice );
            }

            if( technicals->getTechnicalChoiceSet().size() > 0 )
            {
                myOutNotations->addNotationsChoice( technicalNotationChoice );
            }
            
            return myOutNotations;
        }
        
        
        core::NotationsChoicePtr NotationsWriter::makeArticulationsNotationsChoice() const
        {
            auto notationsChoice = core::makeNotationsChoice();
            notationsChoice->setChoice( core::NotationsChoice::Choice::articulations );
            return notationsChoice;
        }


        core::NotationsChoicePtr NotationsWriter::makeOrnamentsNotationsChoice() const
        {
            auto notationsChoice = core::makeNotationsChoice();
            notationsChoice->setChoice( core::NotationsChoice::Choice::ornaments );
            return notationsChoice;
        }

        core::NotationsChoicePtr NotationsWriter::makeTechnicalNotationsChoice() const
        {
            auto notationsChoice = core::makeNotationsChoice();
            notationsChoice->setChoice( core::NotationsChoice::Choice::technical );
            return notationsChoice;
        }
        
        
        void NotationsWriter::addArticulation( const api::MarkData& mark, const core::ArticulationsPtr& outArticulationsPtr ) const
        {
            if( !myConverter.isArticulation( mark.markType ) && !api::isMarkCustom( mark.markType ) )
            {
                return;
            }

            auto articulationsChoice = core::makeArticulationsChoice();
            auto choiceValue = myConverter.convertArticulation( mark.markType );
            articulationsChoice->setChoice( choiceValue );
            outArticulationsPtr->addArticulationsChoice( articulationsChoice );

            if( mark.markType == api::MarkType::accent )
            {
                auto element = articulationsChoice->getAccent();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::strongAccent )
            {
                auto element = articulationsChoice->getStrongAccent();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::staccato )
            {
                auto element = articulationsChoice->getStaccato();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::tenuto )
            {
                auto element = articulationsChoice->getTenuto();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::detachedLegato )
            {
                auto element = articulationsChoice->getDetachedLegato();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::staccatissimo )
            {
                auto element = articulationsChoice->getStaccatissimo();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::spiccato )
            {
                auto element = articulationsChoice->getSpiccato();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::scoop )
            {
                auto element = articulationsChoice->getScoop();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::plop )
            {
                auto element = articulationsChoice->getPlop();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::doit )
            {
                auto element = articulationsChoice->getDoit();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::falloff )
            {
                auto element = articulationsChoice->getFalloff();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::breathMark )
            {
                auto element = articulationsChoice->getBreathMark();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::caesura )
            {
                auto element = articulationsChoice->getCaesura();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::stress )
            {
                auto element = articulationsChoice->getStress();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::unstress )
            {
                auto element = articulationsChoice->getUnstress();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( api::isMarkCustom( mark.markType ) )
            {
                const auto customName = api::getCustomMarkName( mark.markType );
                auto element = articulationsChoice->getOtherArticulation();
                element->setValue( core::XsString{ customName } );
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::otherArticulation )
            {
                auto element = articulationsChoice->getOtherArticulation();
                element->setValue( core::XsString{ mark.name } );
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
        }

        
        void NotationsWriter::addOrnament( const api::MarkData& mark, const core::OrnamentsPtr& outOrnamentsPtr ) const
        {
            if( !isMarkOrnament( mark.markType ) )
            {
                return;
            }

            auto ornamentsChoice = core::makeOrnamentsChoice();
            auto choiceValue = myConverter.convertOrnament( mark.markType );
            ornamentsChoice->setChoice( choiceValue );
            outOrnamentsPtr->addOrnamentsChoice( ornamentsChoice );

            if( mark.markType == api::MarkType::trillMark )
            {
                auto element = ornamentsChoice->getTrillMark();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::turn )
            {
                auto element = ornamentsChoice->getTurn();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::delayedTurn )
            {
                auto element = ornamentsChoice->getDelayedTurn();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::invertedTurn )
            {
                auto element = ornamentsChoice->getInvertedTurn();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::delayedInvertedTurn )
            {
                auto element = ornamentsChoice->getDelayedInvertedTurn();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::verticalTurn )
            {
                auto element = ornamentsChoice->getVerticalTurn();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::shake )
            {
                auto element = ornamentsChoice->getShake();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::wavyLine )
            {
                auto element = ornamentsChoice->getWavyLine();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::mordent )
            {
                auto element = ornamentsChoice->getMordent();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::invertedMordent )
            {
                auto element = ornamentsChoice->getInvertedMordent();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::schleifer )
            {
                auto element = ornamentsChoice->getSchleifer();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( isMarkTremolo( mark.markType ) )
            {
                ornamentsChoice->setChoice( core::OrnamentsChoice::Choice::tremolo );
                auto element = ornamentsChoice->getTremolo();
                auto attributes = element->getAttributes();
                attributes->hasType = true;
                attributes->type = mx::core::StartStopSingle::single;
                setAttributesFromPositionData( mark.positionData, *attributes);
                element->setValue( mx::core::TremoloMarks{ api::numTremoloSlashes( mark.markType ) } );
            }
            else if( api::isMarkCustom( mark.markType ) )
            {
                
            }
            else if( ( mark.markType == api::MarkType::unknownOrnament ) ||
                     ( mark.markType == api::MarkType::otherOrnament ) )
                // TODO - SMUFLKILL - handle custom enum values?
            {
                auto element = ornamentsChoice->getOtherOrnament();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);

                if( !mark.name.empty() )
                {
                    element->setValue( core::XsString{ mark.name } );
                }
            }
        }

        void NotationsWriter::addTechnical( const api::MarkData& mark, const core::TechnicalPtr& outTechnicalPtr ) const
        {
            if( !isMarkTechnical( mark.markType ) )
            {
                return;
            }

            auto technicalChoice = core::makeTechnicalChoice();
            auto choiceValue = myConverter.convertTechnicalMark( mark.markType );
            technicalChoice->setChoice( choiceValue );
            outTechnicalPtr->addTechnicalChoice( technicalChoice );

            if( mark.markType == api::MarkType::upBow )
            {
                auto element = technicalChoice->getUpBow();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::downBow )
            {
                auto element = technicalChoice->getDownBow();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::harmonic )
            {
                auto element = technicalChoice->getHarmonic();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::openString )
            {
                auto element = technicalChoice->getOpenString();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::thumbPosition )
            {
                auto element = technicalChoice->getThumbPosition();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::doubleTongue )
            {
                auto element = technicalChoice->getDoubleTongue();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::tripleTongue )
            {
                auto element = technicalChoice->getTripleTongue();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::stopped )
            {
                auto element = technicalChoice->getStopped();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::snapPizzicato )
            {
                auto element = technicalChoice->getSnapPizzicato();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::heel )
            {
                auto element = technicalChoice->getHeel();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::toe )
            {
                auto element = technicalChoice->getToe();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( mark.markType == api::MarkType::fingernails )
            {
                auto element = technicalChoice->getFingernails();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);
            }
            else if( ( mark.markType == api::MarkType::unknownTechnical ) ||
                    ( mark.markType == api::MarkType::otherTechnical ) )
            {
                auto element = technicalChoice->getOtherTechnical();
                auto attributes = element->getAttributes();
                setAttributesFromPositionData( mark.positionData, *attributes);

                if( !mark.name.empty() )
                {
                    element->setValue( core::XsString{ mark.name } );
                }
            }
        }
    }
}

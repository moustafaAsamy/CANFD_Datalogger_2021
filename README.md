# CANFD_Datalogger_2021
design and implementation of CANFD data logger to read messages and send frames to vehicles CAN network through OBD2 port 


FDCAN CC control register (FDCAN_CCCR)
FDCAN data bit timing and prescaler register (FDCAN_DBTP)
FDCAN nominal bit timing and prescaler register (FDCAN_NBTP)


FDCAN_InitTypeDef

uint32_t ClockDivider;                 /*!< Specifies the FDCAN kernel clock divider.
                                              The clock is common to all FDCAN instances.
                                              This parameter is applied only at initialisation of
                                              first FDCAN instance.
                                              This parameter can be a value of @ref FDCAN_clock_divider.   */

  uint32_t FrameFormat;                  /*!< Specifies the FDCAN frame format.
                                              This parameter can be a value of @ref FDCAN_frame_format     */

  uint32_t Mode;                         /*!< Specifies the FDCAN mode.
                                              This parameter can be a value of @ref FDCAN_operating_mode   */

  FunctionalState AutoRetransmission;    /*!< Enable or disable the automatic retransmission mode.
                                              This parameter can be set to ENABLE or DISABLE               */

  FunctionalState TransmitPause;         /*!< Enable or disable the Transmit Pause feature.
                                              This parameter can be set to ENABLE or DISABLE               */

  FunctionalState ProtocolException;      /*!< Enable or disable the Protocol Exception Handling.
                                              This parameter can be set to ENABLE or DISABLE               */

  uint32_t NominalPrescaler;             /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the nominal bit time quanta.
                                              This parameter must be a number between 1 and 512            */

  uint32_t NominalSyncJumpWidth;         /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a bit to perform
                                              resynchronization.
                                              This parameter must be a number between 1 and 128            */

  uint32_t NominalTimeSeg1;              /*!< Specifies the number of time quanta in Bit Segment 1.
                                              This parameter must be a number between 2 and 256            */

  uint32_t NominalTimeSeg2;              /*!< Specifies the number of time quanta in Bit Segment 2.
                                              This parameter must be a number between 2 and 128            */

  uint32_t DataPrescaler;                /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the data bit time quanta.
                                              This parameter must be a number between 1 and 32             */

  uint32_t DataSyncJumpWidth;            /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a data bit to
                                              perform resynchronization.
                                              This parameter must be a number between 1 and 16             */

  uint32_t DataTimeSeg1;                 /*!< Specifies the number of time quanta in Data Bit Segment 1.
                                              This parameter must be a number between 1 and 32             */

  uint32_t DataTimeSeg2;                 /*!< Specifies the number of time quanta in Data Bit Segment 2.
                                              This parameter must be a number between 1 and 16             */

  uint32_t StdFiltersNbr;                /*!< Specifies the number of standard Message ID filters.
                                              This parameter must be a number between 0 and 28             */

  uint32_t ExtFiltersNbr;                /*!< Specifies the number of extended Message ID filters.
                                              This parameter must be a number between 0 and 8             */

  uint32_t TxFifoQueueMode;              /*!< Tx FIFO/Queue Mode selection.
                                             This parameter can be a value of @ref FDCAN_txFifoQueue_Mode */
**************************************************************************************************************************************************************                                            
FDCAN global filter configuration register (FDCAN_RXGFC)

ypedef struct
{
  uint32_t IdType;           /*!< Specifies the identifier type.
                                  This parameter can be a value of @ref FDCAN_id_type       */

  uint32_t FilterIndex;      /*!< Specifies the filter which will be initialized.
                                  This parameter must be a number between:
                                   - 0 and (SRAMCAN_FLS_NBR-1), if IdType is FDCAN_STANDARD_ID
                                   - 0 and (SRAMCAN_FLE_NBR-1), if IdType is FDCAN_EXTENDED_ID */

  uint32_t FilterType;       /*!< Specifies the filter type.
                                  This parameter can be a value of @ref FDCAN_filter_type.
                                  The value FDCAN_FILTER_RANGE_NO_EIDM is permitted
                                  only when IdType is FDCAN_EXTENDED_ID.                    */

  uint32_t FilterConfig;     /*!< Specifies the filter configuration.
                                  This parameter can be a value of @ref FDCAN_filter_config */

  uint32_t FilterID1;        /*!< Specifies the filter identification 1.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID       */

  uint32_t FilterID2;        /*!< Specifies the filter identification 2.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID       */

} FDCAN_FilterTypeDef;

         
         
         
         
 typedef struct
{
  uint32_t Identifier;          /*!< Specifies the identifier.
                                     This parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                      - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;              /*!< Specifies the identifier type for the message that will be
                                     transmitted.
                                     This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t TxFrameType;         /*!< Specifies the frame type of the message that will be transmitted.
                                     This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;          /*!< Specifies the length of the frame that will be transmitted.
                                      This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;       /*!< Specifies whether the Tx frame will be transmitted with or without
                                     bit rate switching.
                                     This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;            /*!< Specifies whether the Tx frame will be transmitted in classic or
                                     FD format.
                                     This parameter can be a value of @ref FDCAN_format                */

  uint32_t TxEventFifoControl;  /*!< Specifies the event FIFO control.
                                     This parameter can be a value of @ref FDCAN_EFC                   */

  uint32_t MessageMarker;       /*!< Specifies the message marker to be copied into Tx Event FIFO
                                     element for identification of Tx message status.
                                     This parameter must be a number between 0 and 0xFF                */

} FDCAN_TxHeaderTypeDef;   




typedef struct
{
  uint32_t Identifier;            /*!< Specifies the identifier.
                                       This parameter must be a number between:
                                        - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                        - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;                /*!< Specifies the identifier type of the received message.
                                       This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t RxFrameType;           /*!< Specifies the the received message frame type.
                                       This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;            /*!< Specifies the received frame length.
                                        This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator;   /*!< Specifies the error state indicator.
                                       This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;         /*!< Specifies whether the Rx frame is received with or without bit
                                       rate switching.
                                       This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;              /*!< Specifies whether the Rx frame is received in classic or FD
                                       format.
                                       This parameter can be a value of @ref FDCAN_format                */

  uint32_t RxTimestamp;           /*!< Specifies the timestamp counter value captured on start of frame
                                       reception.
                                       This parameter must be a number between 0 and 0xFFFF              */

  uint32_t FilterIndex;           /*!< Specifies the index of matching Rx acceptance filter element.
                                       This parameter must be a number between:
                                        - 0 and (SRAMCAN_FLS_NBR-1), if IdType is FDCAN_STANDARD_ID
                                        - 0 and (SRAMCAN_FLE_NBR-1), if IdType is FDCAN_EXTENDED_ID */

  uint32_t IsFilterMatchingFrame; /*!< Specifies whether the accepted frame did not match any Rx filter.
                                         Acceptance of non-matching frames may be enabled via
                                         HAL_FDCAN_ConfigGlobalFilter().
                                         This parameter can be 0 or 1                                    */

} FDCAN_RxHeaderTypeDef;


ypedef struct
{
  uint32_t Identifier;          /*!< Specifies the identifier.
                                     This parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                      - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;              /*!< Specifies the identifier type for the transmitted message.
                                     This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t TxFrameType;         /*!< Specifies the frame type of the transmitted message.
                                     This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;          /*!< Specifies the length of the transmitted frame.
                                     This parameter can be a value of @ref FDCAN_data_length_code      */

  uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;       /*!< Specifies whether the Tx frame is transmitted with or without bit
                                     rate switching.
                                     This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;            /*!< Specifies whether the Tx frame is transmitted in classic or FD
                                     format.
                                     This parameter can be a value of @ref FDCAN_format                */

  uint32_t TxTimestamp;         /*!< Specifies the timestamp counter value captured on start of frame
                                     transmission.
                                     This parameter must be a number between 0 and 0xFFFF              */

  uint32_t MessageMarker;       /*!< Specifies the message marker copied into Tx Event FIFO element
                                     for identification of Tx message status.
                                     This parameter must be a number between 0 and 0xFF                */

  uint32_t EventType;           /*!< Specifies the event type.
                                     This parameter can be a value of @ref FDCAN_event_type            */

} FDCAN_TxEventFifoTypeDef;


typedef struct
{
  uint32_t LastErrorCode;     /*!< Specifies the type of the last error that occurred on the FDCAN bus.
                                   This parameter can be a value of @ref FDCAN_protocol_error_code */

  uint32_t DataLastErrorCode; /*!< Specifies the type of the last error that occurred in the data phase
                                   of a CAN FD format frame with its BRS flag set.
                                   This parameter can be a value of @ref FDCAN_protocol_error_code */

  uint32_t Activity;          /*!< Specifies the FDCAN module communication state.
                                   This parameter can be a value of @ref FDCAN_communication_state */

  uint32_t ErrorPassive;      /*!< Specifies the FDCAN module error status.
                                   This parameter can be:
                                    - 0 : The FDCAN is in Error_Active state
                                    - 1 : The FDCAN is in Error_Passive state */

  uint32_t Warning;           /*!< Specifies the FDCAN module warning status.
                                   This parameter can be:
                                    - 0 : error counters (RxErrorCnt and TxErrorCnt)
                                          are below the Error_Warning limit of 96
                                    - 1 : at least one of error counters has reached the Error_Warning limit of 96 */

  uint32_t BusOff;            /*!< Specifies the FDCAN module Bus_Off status.
                                   This parameter can be:
                                    - 0 : The FDCAN is not in Bus_Off state
                                    - 1 : The FDCAN is in Bus_Off state */

  uint32_t RxESIflag;         /*!< Specifies ESI flag of last received CAN FD message.
                                   This parameter can be:
                                    - 0 : Last received CAN FD message did not have its ESI flag set
                                    - 1 : Last received CAN FD message had its ESI flag set */

  uint32_t RxBRSflag;         /*!< Specifies BRS flag of last received CAN FD message.
                                   This parameter can be:
                                    - 0 : Last received CAN FD message did not have its BRS flag set
                                    - 1 : Last received CAN FD message had its BRS flag set */

  uint32_t RxFDFflag;         /*!< Specifies if CAN FD message (FDF flag set) has been received
                                   since last protocol status.This parameter can be:
                                    - 0 : No CAN FD message received
                                    - 1 : CAN FD message received */

  uint32_t ProtocolException; /*!< Specifies the FDCAN module Protocol Exception status.
                                   This parameter can be:
                                    - 0 : No protocol exception event occurred since last read access
                                    - 1 : Protocol exception event occurred */

  uint32_t TDCvalue;          /*!< Specifies the Transmitter Delay Compensation Value.
                                   This parameter can be a number between 0 and 127 */

} FDCAN_ProtocolStatusTypeDef;

typedef struct
{
  uint32_t TxErrorCnt;     /*!< Specifies the Transmit Error Counter Value.
                                This parameter can be a number between 0 and 255 */

  uint32_t RxErrorCnt;     /*!< Specifies the Receive Error Counter Value.
                                This parameter can be a number between 0 and 127 */

  uint32_t RxErrorPassive; /*!< Specifies the Receive Error Passive status.
                                This parameter can be:
                                 - 0 : The Receive Error Counter (RxErrorCnt) is below the error passive level of 128
                                 - 1 : The Receive Error Counter (RxErrorCnt)
                                       has reached the error passive level of 128 */

  uint32_t ErrorLogging;   /*!< Specifies the Transmit/Receive error logging counter value.
                                This parameter can be a number between 0 and 255.
                                This counter is incremented each time when a FDCAN protocol error causes the TxErrorCnt
                                or the RxErrorCnt to be incremented. The counter stops at 255; the next increment of
                                TxErrorCnt or RxErrorCnt sets interrupt flag FDCAN_FLAG_ERROR_LOGGING_OVERFLOW */

} FDCAN_ErrorCountersTypeDef;

typedef struct
{
  uint32_t StandardFilterSA; /*!< Specifies the Standard Filter List Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t ExtendedFilterSA; /*!< Specifies the Extended Filter List Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t RxFIFO0SA;        /*!< Specifies the Rx FIFO 0 Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t RxFIFO1SA;        /*!< Specifies the Rx FIFO 1 Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t TxEventFIFOSA;    /*!< Specifies the Tx Event FIFO Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t TxFIFOQSA;        /*!< Specifies the Tx FIFO/Queue Start Address.
                                  This parameter must be a 32-bit word address      */

} FDCAN_MsgRamAddressTypeDef;


typedef struct
{
  FDCAN_GlobalTypeDef         *Instance;        /*!< Register base address     */

  FDCAN_InitTypeDef           Init;             /*!< FDCAN required parameters */

  FDCAN_MsgRamAddressTypeDef  msgRam;           /*!< FDCAN Message RAM blocks  */

  uint32_t                    LatestTxFifoQRequest; /*!< FDCAN Tx buffer index
                                               of latest Tx FIFO/Queue request */

  __IO HAL_FDCAN_StateTypeDef State;            /*!< FDCAN communication state */

  HAL_LockTypeDef             Lock;             /*!< FDCAN locking object      */

  __IO uint32_t               ErrorCode;        /*!< FDCAN Error code          */



} FDCAN_HandleTypeDef; //  contain the base address of module and memory address 


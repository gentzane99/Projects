import { Component, EventEmitter, input, Output } from '@angular/core';
import { IUser } from '../../interfaces/iuser.interface';
import { DeleteButtonComponent } from '../buttons/delete-button/delete-button.component';
import { UpdateButtonComponent } from '../buttons/update-button/update-button.component';
import { ViewDetailsButtonComponent } from '../buttons/view-details-button/view-details-button.component';

@Component({
  selector: 'app-user-card',
  imports: [DeleteButtonComponent, UpdateButtonComponent, ViewDetailsButtonComponent],
  templateUrl: './user-card.component.html',
  styleUrl: './user-card.component.css'
})
export class UserCardComponent {
    miUser = input<IUser>()
    
    @Output() deleteUserEmit: EventEmitter<string> = new EventEmitter()

    onDeleteUser(msg: string){
        this.deleteUserEmit.emit(msg)
    }
}
